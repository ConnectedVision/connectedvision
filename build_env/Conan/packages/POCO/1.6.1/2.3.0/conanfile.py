import os
import shutil
import subprocess
from conans import CMake, ConanFile, model, tools



class POCO(ConanFile):
	name = "POCO"
	version = "1.6.1"
	license = "The Boost Software License 1.0, https://pocoproject.org/license.html"
	url = "https://pocoproject.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	generator = "cmake"
	exports_sources = "PocoMacros.cmake.patch"
	options = {
		"POCO_STATIC": [True, False],
		"ENABLE_XML": [True, False],
		"ENABLE_JSON": [True, False],
		"ENABLE_MONGODB": [True, False],
		"ENABLE_PDF": [True, False],
		"ENABLE_UTIL": [True, False],
		"ENABLE_NET": [True, False],
		"ENABLE_NETSSL": [True, False],
		"ENABLE_NETSSL_WIN": [True, False],
		"ENABLE_CRYPTO": [True, False],
		"ENABLE_DATA": [True, False],
		"ENABLE_DATA_SQLITE": [True, False],
		"ENABLE_DATA_MYSQL": [True, False],
		"ENABLE_DATA_ODBC": [True, False],
		"ENABLE_SEVENZIP": [True, False],
		"ENABLE_ZIP": [True, False],
		"ENABLE_APACHECONNECTOR": [True, False],
		"ENABLE_CPPPARSER": [True, False],
		"ENABLE_POCODOC": [True, False],
		"ENABLE_PAGECOMPILER": [True, False],
		"ENABLE_PAGECOMPILER_FILE2PAGE": [True, False],
		"FORCE_OPENSSL": [True, False], #  "Force usage of OpenSSL even under windows"
		"ENABLE_TESTS": [True, False],
		"POCO_UNBUNDLED": [True, False]
	}
	default_options = '''
POCO_STATIC=True
ENABLE_XML=True
ENABLE_JSON=True
ENABLE_MONGODB=True
ENABLE_PDF=False
ENABLE_UTIL=True
ENABLE_NET=True
ENABLE_NETSSL=True
ENABLE_NETSSL_WIN=False
ENABLE_CRYPTO=True
ENABLE_DATA=True
ENABLE_DATA_SQLITE=True
ENABLE_DATA_MYSQL=False
ENABLE_DATA_ODBC=False
ENABLE_SEVENZIP=False
ENABLE_ZIP=True
ENABLE_APACHECONNECTOR=False
ENABLE_CPPPARSER=False
ENABLE_POCODOC=False
ENABLE_PAGECOMPILER=False
ENABLE_PAGECOMPILER_FILE2PAGE=False
FORCE_OPENSSL=True
ENABLE_TESTS=False
POCO_UNBUNDLED=False
'''

	def config(self):
		self.output.info("")
		self.output.info("---------- config ----------")
		self.output.info("")
		
		if self.options.ENABLE_NETSSL or self.options.ENABLE_CRYPTO or self.options.FORCE_OPENSSL:
			self.output.info("enabled OpenSSL dependency")
			self.requires.add("OpenSSL/1.0.2g@covi/2.3.0", private=False)
			self.options["OpenSSL"].shared = not self.options.POCO_STATIC
		else:
			if "OpenSSL" in self.requires:
				del self.requires["OpenSSL"]



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		zip_name = "poco-" + self.version + "-release.zip"
		tools.download("https://github.com/pocoproject/poco/archive/poco-" + self.version + "-release.zip", zip_name, retry=3, retry_wait=10)
		tools.unzip(zip_name)
		shutil.move("poco-poco-" + self.version + "-release", self.name)
		os.remove(zip_name)
		
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
		self.output.info("build_type: " + str(self.settings.build_type))
		
		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		# create options dict for CMake command
		opts = dict()
		
		# extract the options dict from the options variable
		for item in self.options.items():
			opts[item[0]] = item[1]
		
		if "OpenSSL" in self.requires:
			opts["OPENSSL_ROOT_DIR"] = os.path.dirname(self.deps_cpp_info["OpenSSL"].include_paths[0])
		
		# set the selected C runtime for Visual Studio
		if self.settings.compiler == "Visual Studio":
			flags = ""
			flags += "if(MSVC_IDE)\n"
			flags += "\tset(CMAKE_CXX_FLAGS_DEBUG \"${CMAKE_CXX_FLAGS_DEBUG} /MP /" + str(self.settings.compiler.runtime) + " /Z7\")\n"
			flags += "\tset(CMAKE_CXX_FLAGS_RELEASE \"${CMAKE_CXX_FLAGS_RELEASE} /MP /" + str(self.settings.compiler.runtime) + " /Z7\")\n"
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
		
		# """ Copy required headers, libs and shared libs from the build folder to the package
		# """
		# packages = ["CppUnit", "Crypto", "Data", "Data/MySQL", "Data/ODBC", "Data/SQLite",
					# "Foundation", "JSON", "MongoDB", "Net", "Util", "XML", "Zip"]
		# # Typically includes we want to keep_path=True (default)
		# if self.settings.os == "Windows":
			# packages.append("NetSSL_Win")
		# else:
			# packages.append("NetSSL_OpenSSL")
		
		# for header in packages:
			# self.copy(pattern="*.h", dst="include", src=self.name + "/%s/include" % header)
		
		# # But for libs and dlls, we want to avoid intermediate folders
		# self.copy(pattern="*.lib", dst="lib", src=self.name + "/lib", keep_path=False)
		# self.copy(pattern="*.a",   dst="lib", src=self.name + "/lib", keep_path=False)
		# self.copy(pattern="*.dll", dst="bin", src=self.name + "/bin", keep_path=False)
		# # in linux shared libs are in lib, not bin
		# self.copy(pattern="*.so*", dst="lib", src=self.name + "/lib", keep_path=False)
		# self.copy(pattern="*.dylib", dst="lib", src=self.name + "/lib", keep_path=False)



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libs = [("ENABLE_MONGODB", "PocoMongoDB"),
			("ENABLE_PDF", "PocoPDF"),
			("ENABLE_NETSSL", "PocoNetSSL"),
			("ENABLE_NETSSL_WIN", "PocoNetSSL"),
			("ENABLE_CRYPTO", "PocoCrypto"),
			("ENABLE_DATA_SQLITE", "PocoDataSQLite"),
			("ENABLE_DATA_MYSQL", "PocoDataMySQL"),
			("ENABLE_DATA_ODBC", "PocoDataODBC"),
			("ENABLE_SEVENZIP", "PocoSevenZip"),
			("ENABLE_UTIL", "PocoUtil"),
			("ENABLE_ZIP", "PocoZip"),
			("ENABLE_APACHECONNECTOR", "PocoApacheConnector"),
			("ENABLE_JSON", "PocoJSON"),
			("ENABLE_XML", "PocoXML"),
			("ENABLE_NET", "PocoNet"),
			("ENABLE_DATA", "PocoData")
		]
		
		for flag, lib in libs:
			if getattr(self.options, flag):
				if flag == "ENABLE_NETSSL_WIN" and self.settings.os != "Windows":
					continue
				if flag == "ENABLE_NETSSL" and "OpenSSL" not in self.requires:
					continue
				
				self.cpp_info.libs.append(lib)
		
		self.cpp_info.libs.append("PocoFoundation")
		
		# add "d" to filename of lib Debug version
		if self.settings.build_type == "Debug":
			self.cpp_info.libs = [lib + "d" for lib in self.cpp_info.libs]
		
		if self.settings.os == "Linux":
			self.cpp_info.libs.extend(["pthread", "ssl", "crypto", "dl", "rt"])

		if self.options.POCO_STATIC:
			self.cpp_info.defines.extend(["POCO_STATIC", "POCO_NO_AUTOMATIC_LIBS"])
			
			if self.settings.compiler == "Visual Studio":
				self.cpp_info.libs.extend(["ws2_32", "Iphlpapi"])