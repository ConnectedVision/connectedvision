import os
from conans import ConanFile, CMake

class CppUTest(ConanFile):
	name = "CppUTest"
	version = "3.8"
	license = "BSD 3-clause \"New\" or \"Revised\" License, https://github.com/cpputest/cpputest/blob/master/COPYING"
	url = "https://cpputest.github.io"
	settings = "os", "compiler", "arch", "build_type"
	exports = ["CppUTest.patch"]

	def getOrigName(self):
		return "CppUTest"
	
	def getSrcDirName(self):
		return self.getOrigName().lower()
	
	def getBuildDirName(self):
		return self.getOrigName() + "Build"
	
	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		self.run("git clone --branch v%s https://github.com/cpputest/%s.git" % (self.version, self.getSrcDirName()))
		os.rename(self.getSrcDirName(), "src")
		self.run("git apply < %s.patch --whitespace=nowarn --directory=src" % self.getOrigName())

	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		
		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		cmake = CMake(self)
		
		opts = dict()
		opts["CMAKE_INSTALL_PREFIX"] = "install"
		opts["TESTS"] = False
		
		cmake.configure(defs=opts, source_dir=os.pardir, build_dir=os.path.join("src", self.getBuildDirName()))
		
		cmake.build(target="install")
		
		
	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy("*", dst=".", src=os.path.join("src", self.getBuildDirName(), "install"))
		self.copy("*", dst=os.path.join("include", "Platforms"), src=os.path.join("src", "include", "Platforms"))

	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.cpp_info.libs = ["CppUTest", "CppUTestExt"]
		
		if self.settings.compiler == "Visual Studio":
			self.cpp_info.libs.append("winmm.lib")