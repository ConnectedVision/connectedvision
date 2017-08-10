import glob
import os
import shutil
from conans import ConanFile, tools, model



class FFmpeg(ConanFile):
	name = "FFmpeg"
	version = "3.2.4"
	license = "GNU Lesser General Public License (LGPL) version 2.1, GNU General Public License (GPL) version 2, https://ffmpeg.org/legal.html"
	url = "https://ffmpeg.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64"], "build_type": ["Debug", "Release"]}
	
	
	
	def copyFiles(self, src, dst, ext):
		files = glob.iglob(os.path.join(src, ext))
		
		for file in files:
			if os.path.isfile(file):
				shutil.copy(file, dst)



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
		
		os.unlink(result["filename"])
		
		return result



	def getInstallDir(self):
		return "install"



	def getMsinttypesFlag(self):
		return self.settings.compiler == "Visual Studio" and model.version.Version(str(self.settings.compiler.version)) <= "11"



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(f) ]



	def prepareDownload(self, url, label):
		self.output.info("")
		self.output.info("processing " + label + " ...")
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



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://ffmpeg.org/releases/ffmpeg-" + self.version + ".tar.bz2"
		result = self.getIntoFolder(url, self.name, False)
		
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
		
		if self.settings.os == "Linux":
			self.output.warn("Some libraries are needed to build " + self.name + ". Please enter sudo password if requested...")
			self.run("sudo apt-get install -y yasm")
		
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
		
		if self.settings.build_type == "Debug":
			params += " --enable-debug"
		
		if self.settings.compiler == "Visual Studio": 
			# use --disable-encoder=ffv1 flag at least for Visual Studio 2010 to avoid make compilation loop
			# other Visual Studio versions than 2010 have not been tested
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

				for file in os.listdir(libDir):
					if file.endswith(".a"):
						base = os.path.splitext(file)[0]
						src = os.path.join(libDir, file)
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