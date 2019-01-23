import glob
import os
import re
import subprocess
from conans import CMake, ConanFile, model, tools



class POCO(ConanFile):
	name = "POCO"
	version = "1.9.0"
	license = "The Boost Software License 1.0, https://pocoproject.org/license.html"
	url = "https://pocoproject.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	generator = "cmake"
	exports_sources = "PocoMacros.cmake.patch"
	options = {
		"ENABLE_CPPPARSER": [True, False],
		"ENABLE_CRYPTO": [True, False],
		"ENABLE_DATA": [True, False],
		"ENABLE_DATA_MYSQL": [False],
		"ENABLE_DATA_ODBC": [True, False],
		"ENABLE_DATA_SQLITE": [True, False],
		"ENABLE_JSON": [True, False],
		"ENABLE_MONGODB": [True, False],
		"ENABLE_NET": [True, False],
		"ENABLE_NETSSL": [True, False],
		"ENABLE_NETSSL_WIN": [True, False],
		"ENABLE_PAGECOMPILER": [True, False],
		"ENABLE_PAGECOMPILER_FILE2PAGE": [True, False],
		"ENABLE_PDF": [True, False],
		"ENABLE_POCODOC": [True, False],
		"ENABLE_SEVENZIP": [True, False],
		"ENABLE_TESTS": [True, False],
		"ENABLE_UTIL": [True, False],
		"ENABLE_XML": [True, False],
		"ENABLE_ZIP": [True, False],
		"FORCE_OPENSSL": [True, False],
		"POCO_STATIC": [True],
		"POCO_UNBUNDLED": [True, False]
	}
	default_options = {
		"ENABLE_CPPPARSER": False,
		"ENABLE_CRYPTO": True,
		"ENABLE_DATA": True,
		"ENABLE_DATA_MYSQL": False,
		"ENABLE_DATA_ODBC": False,
		"ENABLE_DATA_SQLITE": True,
		"ENABLE_JSON": True,
		"ENABLE_MONGODB": True,
		"ENABLE_NET": True,
		"ENABLE_NETSSL": True,
		"ENABLE_NETSSL_WIN": False,
		"ENABLE_PAGECOMPILER": False,
		"ENABLE_PAGECOMPILER_FILE2PAGE": False,
		"ENABLE_PDF": False,
		"ENABLE_POCODOC": False,
		"ENABLE_SEVENZIP": False,
		"ENABLE_TESTS": False,
		"ENABLE_UTIL": True,
		"ENABLE_XML": True,
		"ENABLE_ZIP": True,
		"FORCE_OPENSSL": True,
		"POCO_STATIC": True,
		"POCO_UNBUNDLED": False
	}



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



	def configure(self):
		self.output.info("")
		self.output.info("---------- configure ----------")
		self.output.info("")
		
		if self.options.ENABLE_NETSSL or self.options.ENABLE_CRYPTO or self.options.FORCE_OPENSSL:
			self.output.info("enabled OpenSSL dependency")
			self.requires.add("OpenSSL/1.0.2g@covi/2.4.0", private=False)
			self.options["OpenSSL"].shared = not self.options.POCO_STATIC
		else:
			if "OpenSSL" in self.requires:
				del self.requires["OpenSSL"]



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://github.com/pocoproject/poco/archive/poco-" + self.version + "-release.zip"
		
		self.download(url, sha256="6EA78A5A852C9E596DB2BC059E0DA47F5AE52147817206BEE06D165A4845851C")
		
		if self.settings.compiler == "Visual Studio" and model.version.Version(str(self.settings.compiler.version)) > "10":
			patchFile = os.path.join(self.source_folder, "PocoMacros.cmake.patch")
			subprocess.check_call(["git", "apply", "--ignore-space-change", patchFile], cwd=os.path.join(self.name, "cmake"))
			os.remove(patchFile)



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
		
		# create options dict for CMake command
		opts = dict()
		
		# extract the options dict from the options variable
		for item in self.options.items():
			opts[item[0]] = item[1]
		
		if "OpenSSL" in self.requires:
			opts["OPENSSL_ROOT_DIR"] = os.path.dirname(self.deps_cpp_info["OpenSSL"].include_paths[0])
		
		# set the selected C runtime for Visual Studio
		if self.settings.compiler == "Visual Studio":
			opts["POCO_MT"] = "True" if "MT" in str(self.settings.compiler.runtime) else "False"
			opts["ENABLE_MSVC_MP"] = "True"
		
			flags = ""
			flags += "if(MSVC_IDE)\n"
			flags += "\tset(CMAKE_CXX_FLAGS_DEBUG \"${CMAKE_CXX_FLAGS_DEBUG} /Z7\")\n"
			flags += "\tset(CMAKE_CXX_FLAGS_RELEASE \"${CMAKE_CXX_FLAGS_RELEASE} /Z7\")\n"
			flags += "else()"
			
			tools.replace_in_file(os.path.join(self.name, "CMakeLists.txt"), "if(NOT MSVC_IDE)", flags)
		
		opts["CMAKE_INSTALL_PREFIX"] = "install"
		
		cmake = CMake(self)
		
		buildDir = os.path.join(self.name, "build_conan")
		
		os.makedirs(buildDir)
		
		cmake.configure(defs=opts, source_dir=os.pardir, build_dir=buildDir)
		
		cmake.build(target="install")



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		installDir = os.path.join(self.name, "build_conan", "install")
		
		self.copy("*", dst="include", src=os.path.join(installDir, "include"))
		self.copy("*.*", dst="lib", src=os.path.join(installDir, "lib"))



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libDir = os.path.join(self.package_folder, self.cpp_info.libdirs[0])
		
		with tools.chdir(libDir):
			if self.settings.os == "Windows":
				self.cpp_info.libs = glob.glob("*.lib")
				self.cpp_info.libs.extend(["ws2_32", "Iphlpapi"])
			else:
				r = re.compile(r"lib(.+?)\.a")
				libs = [re.match(r, f).group(1) for f in glob.glob("*.a")]
				
				# adjust the lib order for Linux/GCC
				libsSubsetSorted = ["PocoCrypto", "PocoUtil", "PocoJSON", "PocoXML", "PocoFoundation"]

				# add "d" filename suffix for debug build
				if self.settings.build_type == "Debug":
					libsSubsetSorted = [lib + "d" for lib in libsSubsetSorted]
				
				for lib in libsSubsetSorted:
					if lib in libs:
						libs.remove(lib)
						libs.append(lib)
				
				self.cpp_info.libs = libs
				self.cpp_info.libs.extend(["pthread", "ssl", "crypto", "dl", "rt"])
				
				# adjust the lib order as it is important for linking using GCC on Linux
		
			if self.options.POCO_STATIC:
				self.cpp_info.defines.extend(["POCO_STATIC", "POCO_NO_AUTOMATIC_LIBS"])