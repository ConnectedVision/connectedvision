import glob
import os
import shutil
from conans import CMake, ConanFile, tools



class CrashRpt(ConanFile):
	name = "CrashRpt"
	version = "1.4.3"
	license = "New BSD license, http://crashrpt.sourceforge.net/License.txt"
	url = "http://crashrpt.sourceforge.net"
	settings = {"os": ["Windows"], "compiler": ["Visual Studio"], "arch": ["x86", "x86_64"], "build_type": ["Debug", "Release"]}
	generator = "cmake"



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		self.run("git clone https://git.code.sf.net/p/crashrpt/code " + self.name)



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		opts = dict()
		opts["CRASHRPT_BUILD_SHARED_LIBS"] = True
		opts["CRASHRPT_LINK_CRT_AS_DLL"] = True
		
		cmake = CMake(self)
		
		buildDir = os.path.join(self.name, "build")
		
		os.makedirs(buildDir)
		
		cmake.configure(defs=opts, source_dir=os.pardir, build_dir=buildDir)
		
		cmake.build()



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy("*", dst="include", src=os.path.join(os.path.join(self.name, "include")))
		
		buildDir = os.path.join(os.getcwd(), self.name, "build")
		libDir = os.path.join(buildDir, "lib")
		
		# determine the path of the actual lib directory since CrashRpt has no install step and the build output of the 64 bit build is contained in a subdirectory of the lib directory
		if not glob.glob(os.path.join(libDir, "*.lib")):
			libDir = os.path.dirname(glob.glob(os.path.join(libDir, "*", "*.lib"))[0])
			
		binDir = os.path.join(buildDir, "bin")
		
		# determine the path of the actual bin directory since CrashRpt has no install step and the build output of the 64 bit build is contained in a subdirectory of the bin directory
		if not glob.glob(os.path.join(binDir, "*.exe")):
			binDir = os.path.dirname(glob.glob(os.path.join(binDir, "*", "*.exe"))[0])
			
		langDir = os.path.join(self.name, "lang_files")
		
		self.copy("*.lib", src=libDir, dst="lib")
		self.copy("*.dll", src=binDir, dst="bin")
		self.copy("CrashSender*.exe", src=binDir, dst="bin")
		shutil.copyfile(os.path.join(langDir, "crashrpt_lang_EN.ini"), os.path.join(langDir, "crashrpt_lang.ini"))
		self.copy("crashrpt_lang.ini", src=langDir, dst="bin")



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.cpp_info.defines = ["CRASHRPT_ENABLED"]
		
		libDir = os.path.join(self.package_folder, self.cpp_info.libdirs[0])
		
		with tools.chdir(libDir):
			self.cpp_info.libs = glob.glob("*.lib")
		
		self.cpp_info.cppflags = ["/Zi", "/Oy-"]
		
		# the exelinkflags don't seem to work for Visual Studio (Conan 0.25.1) as forward slashes are always converted to backslashes
		# self.cpp_info.exelinkflags = ["/DEBUG"]