from conans import ConanFile
from conans import tools
import os
import platform
import re
import sys


class BoostConan(ConanFile):
	name = "Boost"
	version = "1.58.0"
	license = "Boost Software License, http://www.boost.org/LICENSE_1_0.txt"
	url = "http://www.boost.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	FOLDER_NAME = "boost_%s" % version.replace(".", "_")
	options = {"shared": [True, False], "header_only": [True, False]}
	default_options = "shared=False", "header_only=False"
	counter_config = 0

	def config(self):
		self.output.info("")
		self.output.info("---------- config ----------")
		self.output.info("")
		
		# If header only, the compiler, etc, does not affect the package!
		self.counter_config += 1
		# config is called twice, one before receive the upper dependencies and another before
		if self.options.header_only and self.counter_config==2:
			self.output.info("HEADER ONLY")
			self.settings.clear()
			self.options.remove("shared")
		if not self.options.header_only and self.settings.os == "Windows" and self.options.shared and "MT" in str(self.settings.compiler.runtime):
			self.options.shared = False

	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		zip_name = "%s.zip" % self.FOLDER_NAME if sys.platform == "win32" else "%s.tar.gz" % self.FOLDER_NAME
		url = "http://sourceforge.net/projects/boost/files/boost/%s/%s/download" % (self.version, zip_name)
		self.output.info("Downloading %s..." % url)
		tools.download(url, zip_name, retry=3, retry_wait=10)
		tools.unzip(zip_name, ".")
		os.unlink(zip_name)

	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		
		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		if self.options.header_only:
			return
		
		if self.settings.os == "Windows":
			command = "bootstrap"
		else:
			command = "./bootstrap.sh"

		try:
			with tools.chdir(self.FOLDER_NAME):
				self.run(command)
		except:
			with tools.chdir(self.FOLDER_NAME):
				if self.settings.os == "Windows":
					self.run("type bootstrap.log")
				else:
					self.run("cat bootstrap.log")
			raise

		flags = []
		
		if self.settings.compiler == "Visual Studio":
			flags.append("toolset=msvc-%s.0" % self.settings.compiler.version)
		elif self.settings.arch == "armv7hf" and not re.match("arm.*", platform.machine()):
			flags.append("toolset=gcc-arm")
			
			if not os.environ.has_key("CXX"):
				raise Exception("failed to extract compiler from environment variable \"CXX\" (variable is not set)")
			
			result = re.search(r"(.*g\+\+)$", os.environ.get("CXX"), re.M|re.I)
			
			if not result:
				raise Exception("Failed to extract compiler from environment variable \"CXX\". Variable value \"" + os.environ.get("CXX") + "\" does not end with \"g++\", e.g. \"arm-linux-gnueabihf-g++\".")
			
			# set the compiler directly by editing the project-config.jam instead of specifying it in a user-config.jam file in combination with the BOOST_BUILD_PATH environment variable since a possibly existing user-config.jam in the HOME directory would take precedence over BOOST_BUILD_PATH
			with tools.chdir(self.FOLDER_NAME):			
				with open("project-config.jam", "r+") as f:
					content = f.read()
					content = re.sub(r"([ \t]*)using gcc[ \t]*;*", r"\1using gcc : arm : " + result.group(1) + " ;", content)
					f.seek(0)
					f.write(content)
					f.truncate()
		
		flags.append("link=%s" % ("static" if not self.options.shared else "shared"))
		
		if self.settings.compiler == "Visual Studio" and self.settings.compiler.runtime:
			flags.append("runtime-link=%s" % ("static" if "MT" in str(self.settings.compiler.runtime) else "shared"))
		
		flags.append("variant=%s" % str(self.settings.build_type).lower())
		
		if self.settings.arch != "armv7hf":
			flags.append("address-model=%s" % ("32" if self.settings.arch == "x86" else "64"))
		
		b2_flags = " ".join(flags)

		if self.settings.os == "Windows":
			command = "b2"
		else:
			command = "./b2"
		
		command += " " + b2_flags + " -j " + str(tools.cpu_count()) + " -s NO_BZIP2=1 --abbreviate-paths --without-python"

		if self.settings.arch == "armv7hf":
			command += " --without-context --without-coroutine"
		
		self.output.warn(command)

		with tools.chdir(self.FOLDER_NAME):
			self.run(command)

	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy(pattern="*", dst="include/boost", src="%s/boost" % self.FOLDER_NAME)
		self.copy(pattern="*.a", dst="lib", src="%s/stage/lib" % self.FOLDER_NAME)
		self.copy(pattern="*.so", dst="lib", src="%s/stage/lib" % self.FOLDER_NAME)
		self.copy(pattern="*.so.*", dst="lib", src="%s/stage/lib" % self.FOLDER_NAME)
		self.copy(pattern="*.dylib*", dst="lib", src="%s/stage/lib" % self.FOLDER_NAME)
		self.copy(pattern="*.lib", dst="lib", src="%s/stage/lib" % self.FOLDER_NAME)
		self.copy(pattern="*.dll", dst="bin", src="%s/stage/lib" % self.FOLDER_NAME)
		
	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		if not self.options.header_only:
			if self.options.shared:
				self.cpp_info.defines.append("BOOST_ALL_DYN_LINK")
			else:
				self.cpp_info.defines.append("BOOST_USE_STATIC_LIBS")

			libs = ("atomic chrono container context coroutine date_time exception filesystem "
					"graph iostreams locale log_setup log math_c99 math_c99f math_c99l math_tr1 "
					"math_tr1f math_tr1l prg_exec_monitor program_options random regex serialization "
					"signals system test_exec_monitor thread timer unit_test_framework wave "
					"wserialization").split()

		if self.settings.os != "Windows":
				if self.settings.arch == "armv7hf":
					libs.remove("context")
					libs.remove("coroutine")
				
				self.cpp_info.libs.extend(["boost_%s" % lib for lib in libs])
		elif self.settings.os == "Windows":
			win_libs = []
			# http://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html
			visual_version = int(str(self.settings.compiler.version)) * 10
			runtime = "mt"# str(self.settings.compiler.runtime).lower()
			
			abi_tags = []
			if self.settings.compiler.runtime in ("MTd", "MT"):
				abi_tags.append("s")
			
			if self.settings.build_type == "Debug":
				abi_tags.append("gd")
			
			abi_tags = ("-%s" % "".join(abi_tags)) if abi_tags else ""
			
			version = "_".join(self.version.split(".")[0:2])
			suffix = "vc%d-%s%s-%s" % (visual_version, runtime, abi_tags, version)
			prefix = "lib" if not self.options.shared else ""
			
			
			win_libs.extend(["%sboost_%s-%s" % (prefix, lib, suffix) for lib in libs if lib not in ["exception", "test_exec_monitor"]])
			win_libs.extend(["libboost_exception-%s" % suffix, "libboost_test_exec_monitor-%s" % suffix])
			
			#self.output.warn("EXPORTED BOOST LIBRARIES: %s" % win_libs)
			self.cpp_info.libs.extend(win_libs)
			self.cpp_info.defines.extend(["BOOST_ALL_NO_LIB"]) # DISABLES AUTO LINKING! NO SMART AND MAGIC DECISIONS THANKS!