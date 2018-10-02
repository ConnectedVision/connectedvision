import glob
import os
import platform
import re
import shutil
from conans import ConanFile, tools, model



class FFmpeg(ConanFile):
	name = "FFmpeg"
	version = "3.2.4"
	license = "GNU Lesser General Public License (LGPL) version 2.1, GNU General Public License (GPL) version 2, https://ffmpeg.org/legal.html"
	url = "https://ffmpeg.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	
	
	
	def copyFiles(self, src, dst, ext):
		files = glob.iglob(os.path.join(src, ext))
		
		for f in files:
			if os.path.isfile(f):
				shutil.copy(f, dst)



	def getIntoFolder(self, url, label, subdir=True):
		result = self.prepareDownload(url, label)
		tools.download(url, result["filename"], retry=3, retry_wait=10)
		
		directory = ""
		
		if subdir:
			directory = os.path.join(os.getcwd(), result["name"])
		
		if result["extension"] == ".xz":
			tools.untargz(result["filename"], directory)
		else:
			tools.unzip(result["filename"], directory)
		
		os.remove(result["filename"])
		
		return result



	def getInstallDir(self):
		return "install"



	def getMsinttypesFlag(self):
		return self.settings.compiler == "Visual Studio" and model.version.Version(str(self.settings.compiler.version)) <= "11"



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(f) ]



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
			self.build_requires("MSYS2/2016.10.25@covi/stable")
		
			if self.getMsinttypesFlag():
				self.build_requires("c99-to-c89/1.0.3@covi/stable")
		else:
			self.build_requires("NASM/2.13.02@covi/stable")



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://ffmpeg.org/releases/ffmpeg-" + self.version + ".tar.bz2"
		self.getIntoFolder(url, self.name, False)
		
		dirnames = self.getSubdirectories(".")
		
		if len(dirnames) < 1:
			raise Exception("archive does not contain any subdirectories")
		
		os.rename(dirnames[0], self.name)
		
		if self.getMsinttypesFlag():
			url = "https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/msinttypes/msinttypes-r26.zip"
			result = self.getIntoFolder(url, "msinttypes")
			self.copyFiles(result["name"], self.name, "*.h")
			shutil.rmtree(result["name"])



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		
		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		ffmpegInstallDir = self.getInstallDir()
		
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
			params += " --disable-ffserver"
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
		
		installDir = os.path.join(self.name, self.getInstallDir())
		self.copy("*", dst="include", src=os.path.join(installDir, "include"))
		
		if self.getMsinttypesFlag():
			self.copy("inttypes.h", dst="include", src=self.name)

		self.copy("*", dst="lib", src=os.path.join(installDir, "lib"))



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		if self.settings.os == "Windows":
			self.cpp_info.libs = ["libavcodec", "libavfilter", "libavformat", "libavutil", "libswresample", "libswscale", "Secur32"]
		else:
			self.cpp_info.libs = ["avformat", "avfilter", "avcodec", "swscale", "avutil", "swresample"]
			
			if model.version.Version(str(self.settings.compiler.version)) < "4.8":
				self.cpp_info.defines = ["__STDC_CONSTANT_MACROS"]