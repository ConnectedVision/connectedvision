import os
import platform
import re
import shutil
from conans import ConanFile, tools



class Boost(ConanFile):
	name = "Boost"
	version = "1.68.0"
	license = "Boost Software License, http://www.boost.org/LICENSE_1_0.txt"
	url = "http://www.boost.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	
	
	
	def download(self, url, dst="", subdir=False, sha256=""):
		"""
		Downloads an archive file from the specified URL, optionaly compares its SHA256 to the specified value and extracts the archive.
		
		Args:
		- url: source URL
		- dst: destination directory. If empty, then a directory name derived from the download link is used.
		- subdir: If False and the archive contains only a single root directory, then the content of that directory is extracted into the destination directory.
		- sha256: The expected SHA256 hash of the downloaded file to be compared to the actual file hash. If empty, then the check is omitted.
		"""
		
		self.output.info("")
		self.output.info("downloading " + url + " ...")
		
		filename = os.path.basename(url)
		extension = os.path.splitext(filename)[1]
		
		tools.download(url, filename, retry=3, retry_wait=10)
		
		if sha256:
			sha256File = tools.sha256sum(filename)
			
			if sha256.upper() != sha256File.upper():
				raise Exception("SHA256 of downloaded file (" + sha256File.upper() + ") does not match expected value (" + sha256.upper() + ")")
		
		self.output.info("SHA256 of downloaded file matches expected value (" + sha256.upper() + ")")
		
		if not dst:
			dst = os.path.join(os.getcwd(), self.name)
		
		self.output.info("extracting " + filename + " ...")
		
		if extension == ".xz":
			tools.untargz(filename, dst)
		else:
			tools.unzip(filename, dst)
		
		print("")
		
		content = os.listdir(dst)
		
		if not subdir and len(content) == 1 and os.path.isdir(os.path.join(dst, content[0])):
			tempDir = os.path.join(os.path.dirname(dst), self.name + "Temp")
			os.rename(os.path.join(dst, content[0]), tempDir)
			
			if os.path.isdir(dst):
				os.rmdir(dst)
			
			os.rename(tempDir, dst)
		
		os.remove(filename)
	
	
	
	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		archiveFilename = "boost_" + self.version.replace(".", "_") + "." + ("zip" if self.settings.os == "Windows" else "tar.gz")
		url = "https://dl.bintray.com/boostorg/release/" + self.version + "/source/" + archiveFilename
		
		if self.settings.os == "Windows":
			sha256 = "3B1DB0B67079266C40B98329D85916E910BBADFC3DB3E860C049056788D4D5CD"
		else:
			sha256 = "DA3411EA45622579D419BFDA66F45CD0F8C32A181D84ADFA936F5688388995CF"
		
		self.download(url, sha256=sha256)
		
		# remove subdirectories with name "doc" which contain ~50% (~30,000) of all files and are not required for building and not packaged
		# copying them from source to build directory takes very long on Windows (not on Linux) even when using an SSD
		for dirPath, dirNames, filenames in os.walk(self.source_folder):
			dirPath = os.path.abspath(dirPath)
			
			try:
				if os.path.basename(dirPath) == "doc":
					shutil.rmtree(dirPath)
			except:
				pass



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("compiler  : " + str(self.settings.compiler) + " " + str(self.settings.compiler.version))
		self.output.info("build type: " + str(self.settings.build_type))

		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		else:
			self.output.info("libcxx    : " + str(self.settings.compiler.libcxx))
		
		if self.settings.os == "Windows":
			command = "bootstrap.bat vc" + ("141" if self.settings.compiler.version == "15" else str(self.settings.compiler.version))
		else:
			command = "./bootstrap.sh"
		
		try:
			with tools.chdir(self.name):
				with tools.vcvars(self.settings) if self.settings.compiler == "Visual Studio" else tools.no_op():
					self.run(command)
		except:
			with tools.chdir(self.name):
				if self.settings.os == "Windows":
					self.run("type bootstrap.log")
				else:
					self.run("cat bootstrap.log")
			raise

		flags = []
		
		if self.settings.compiler == "Visual Studio":
			flags.append("toolset=msvc-" + ("14.1" if self.settings.compiler.version == "15" else str(self.settings.compiler.version) + ".0"))
		elif self.settings.arch == "armv7hf" and not re.match("arm.*", platform.machine()):
			flags.append("toolset=gcc-arm")
			
			if not "CXX" in os.environ:
				raise Exception("failed to extract compiler from environment variable \"CXX\" (variable is not set)")
			
			result = re.search(r"(.*g\+\+)$", os.environ.get("CXX"), re.M|re.I)
			
			if not result:
				raise Exception("Failed to extract compiler from environment variable \"CXX\". Variable value \"" + os.environ.get("CXX") + "\" does not end with \"g++\", e.g. \"arm-linux-gnueabihf-g++\".")
			
			# set the compiler directly by editing the project-config.jam instead of specifying it in a user-config.jam file in combination with the BOOST_BUILD_PATH environment variable since a possibly existing user-config.jam in the HOME directory would take precedence over BOOST_BUILD_PATH
			with tools.chdir(self.name):			
				with open("project-config.jam", "r+") as f:
					content = f.read()
					content = re.sub(r"([ \t]*)using gcc[ \t]*;*", r"\1using gcc : arm : " + result.group(1) + " ;", content)
					f.seek(0)
					f.write(content)
					f.truncate()
		
		flags.append("link=static")
		
		if self.settings.compiler == "Visual Studio" and self.settings.compiler.runtime:
			flags.append("runtime-link=" + ("static" if "MT" in str(self.settings.compiler.runtime) else "shared"))
		
		flags.append("variant=" + str(self.settings.build_type).lower())
		
		if self.settings.arch != "armv7hf":
			flags.append("address-model=" + ("32" if self.settings.arch == "x86" else "64"))
		
		b2Flags = " ".join(flags)

		if self.settings.os == "Windows":
			command = "b2"
		else:
			command = "./b2"
		
		command += " " + b2Flags + " -j " + str(tools.cpu_count()) + " -s NO_BZIP2=1 --abbreviate-paths --without-python"

		if self.settings.arch == "armv7hf":
			command += " --without-context --without-coroutine"
		
		self.output.warn(command)

		with tools.chdir(self.name):
			self.run(command)

	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy(pattern="*", dst="include/boost", src=os.path.join(self.name, "boost"))
		
		libDir = os.path.join(self.name, "stage", "lib")
		
		if self.settings.compiler == "Visual Studio":
			self.copy(pattern="*.lib", dst="lib", src=libDir)
		else:
			self.copy(pattern="*.a", dst="lib", src=libDir)
		
	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.cpp_info.defines.append("BOOST_USE_STATIC_LIBS")
		
		libNames = ["math", "wave", "container", "contract", "exception", "graph", "iostreams", "locale", "log", "program_options", "random", "regex", "mpi", "serialization", "signals", "coroutine", "fiber", "context", "timer", "thread", "chrono", "date_time", "atomic", "filesystem", "system", "graph_parallel", "python", "stacktrace", "test", "type_erasure"]
		
		libFiles = tools.collect_libs(self)
		
		if self.settings.compiler == "gcc":
			libs = []
			
			for libName in libNames:
				r = re.compile("boost_" + libName + "[^-$]*")
				
				libFilesSubset = [r.match(libFile).group(0) for libFile in libFiles if r.match(libFile)]
				
				if libFilesSubset:
					libs.extend(libFilesSubset)
			
			libs.extend(list(set(libFiles) - set(libs)))
		
			if self.settings.arch == "armv7hf":
				r = re.compile("boost_(context|coroutine)[^-$]*")
				
				for libFile in libFiles:
					if r.match(libFile):
						libs.remove(libFile)
			
			self.cpp_info.libs = libs
		else:
			self.cpp_info.libs = tools.collect_libs(self)