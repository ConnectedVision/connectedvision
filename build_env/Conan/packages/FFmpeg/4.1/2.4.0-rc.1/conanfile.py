import os
import platform
import re
from conans import ConanFile, tools, model



class FFmpeg(ConanFile):
	name = "FFmpeg"
	version = "4.1"
	license = "GNU Lesser General Public License (LGPL) version 2.1, GNU General Public License (GPL) version 2, https://ffmpeg.org/legal.html"
	url = "https://ffmpeg.org"
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
	
	
	
	def getMsinttypesFlag(self):
		return self.settings.compiler == "Visual Studio" and model.version.Version(str(self.settings.compiler.version)) <= "11"



	def prepareDownload(self, url, label):
		self.output.info("")
		self.output.info("downloading " + label + " from " + url)
		filename = os.path.basename(url)
		name = os.path.splitext(filename)[0]
		extension = os.path.splitext(filename)[1]
		return { "name": name, "filename": filename, "extension": extension }



	def build_requirements(self):
		self.output.info("")
		self.output.info("---------- build_requirements ----------")
		self.output.info("")
		
		if self.settings.os == "Windows":
			self.build_requires("MSYS2/2016.10.25@covi/2.3.0")
		
			if self.getMsinttypesFlag():
				self.build_requires("c99-to-c89/1.0.3@covi/2.3.0")
		else:
			self.build_requires("NASM/2.13.02@covi/2.3.0")



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://ffmpeg.org/releases/ffmpeg-" + self.version + ".tar.bz2"
		self.download(url, sha256="B684FB43244A5C4CAAE652AF9022ED5D85CE15210835BCE054A33FB26033A1A5")
		
		if self.getMsinttypesFlag():
			url = "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/msinttypes/msinttypes-r26.zip"
			self.download(url, sha256="6E66D88DE18AAC0775890E94AA621853AA1D572136E3783CE130510D8FB6A55D")



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
		
		ffmpegInstallDir = "install"
		
		params = ""
		params += " --disable-doc"
		params += " --disable-bzlib"
		params += " --disable-lzma"
		params += " --disable-zlib"
		
		if self.settings.os == "Windows":
			params += " --disable-avdevice"
			params += " --disable-ffmpeg"
			params += " --disable-ffplay"
			params += " --disable-ffprobe"
			params += " --disable-iconv"
			params += " --disable-libopenjpeg"
			params += " --enable-asm"
			params += " --enable-yasm"
			params += " --prefix=\"" + tools.unix_path(ffmpegInstallDir) + "\""
		else:
			params += " --prefix=\"" + ffmpegInstallDir + "\""

		
		if self.settings.build_type == "Debug":
			params += " --enable-debug"
		
		if self.settings.compiler == "Visual Studio": 
			# use --disable-encoder=ffv1 flag for Visual Studio 2010 to avoid make compilation loop
			if self.settings.compiler.version == "10":
				params += " --disable-encoder=ffv1"
			
			params += " --toolchain=msvc"
			params += " --extra-cflags=\"-" + str(self.settings.compiler.runtime) + "\""
			params += " --extra-cxxflags=\"-" + str(self.settings.compiler.runtime) + "\""
			
			if self.settings.arch == "x86":
				params += " --arch=x86"
				params += " --target-os=win32"
			else:
				params += " --arch=amd64"
			
			if self.settings.compiler.runtime == "MT":
				params += " --extra-ldflags=\"/NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:msvcrtd.lib /NODEFAULTLIB:libcmtd.lib\""
			elif self.settings.compiler.runtime == "MTd":
				params += " --extra-ldflags=\"/NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:msvcrt.lib /NODEFAULTLIB:msvcrtd.lib /NODEFAULTLIB:libcmt.lib\""
			elif self.settings.compiler.runtime == "MD":
				params += " --extra-ldflags=\"/NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib\""
			elif self.settings.compiler.runtime == "MDd":
				params += " --extra-ldflags=\"/NODEFAULTLIB:libc.lib /NODEFAULTLIB:libcd.lib /NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrt.lib\""
			else:
				raise Exception("unsupported runtime: " + str(self.settings.compiler.runtime))
		elif self.settings.arch == "armv7hf" and not re.match("arm.*", platform.machine()):
			if not "CC" in os.environ:
				raise Exception("failed to extract compiler from environment variable \"CC\" (variable is not set)")
			
			result = re.search("(.*)gcc$", os.environ.get("CC"), re.M|re.I)
			
			if not result:
				raise Exception("failed to extract compiler from environment variable \"CC\" (variable value does not end with \"gcc\", e.g. \"arm-linux-gnueabihf-gcc\")")
			
			params += " --enable-cross-compile --cross-prefix=" + result.group(1) + " --arch=armhf --target-os=linux"
		
		with tools.chdir(self.name):
			command = ""
						
			if self.settings.os == "Windows":
				if self.settings.compiler == "Visual Studio":
					command += tools.vcvars_command(self.settings)
				
				command += " && bash.exe -c \"./configure" + params + "\""
				command += " && bash.exe -c \"make -j" + str(tools.cpu_count()) + " install\""
			else:
				command = "./configure" + params
				command += " && make -j" + str(tools.cpu_count()) + " install"
			
			self.output.info("")
			self.output.info("executing the following commands:")
			self.output.info(command)
			
			self.run(command)
			
			if not os.path.exists(ffmpegInstallDir):
				raise Exception("install directory does not exist: " + ffmpegInstallDir)
			
			if self.settings.os == "Windows":
				libDir = os.path.join(ffmpegInstallDir, "lib")

				for f in os.listdir(libDir):
					if f.endswith(".a"):
						base = os.path.splitext(f)[0]
						src = os.path.join(libDir, f)
						dst = os.path.join(libDir, base + ".lib")
						os.rename(src, dst)
			



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		installDir = os.path.join(self.name, "install")
		self.copy("*", dst="include", src=os.path.join(installDir, "include"))
		
		if self.getMsinttypesFlag():
			self.copy("inttypes.h", dst="include", src=self.name)

		self.copy("*", dst="lib", src=os.path.join(installDir, "lib"))



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libFiles = tools.collect_libs(self)

		if self.settings.os == "Windows":
			self.cpp_info.libs = libFiles
			self.cpp_info.libs.extend(["Secur32", "Ws2_32", "bcrypt"])
		else:
			libs = []
			libNames = ["avdevice", "avformat", "avfilter", "avcodec", "swscale", "avutil", "swresample"]

			for libName in libNames:
				if libName in libFiles:
					libs.append(libName)
			
			libs.extend(list(set(libFiles) - set(libs)))
			
			self.cpp_info.libs = libs
			
			if model.version.Version(str(self.settings.compiler.version)) < "4.8":
				self.cpp_info.defines = ["__STDC_CONSTANT_MACROS"]