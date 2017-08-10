import os
import re
from conans import ConanFile, CMake, tools

VERSION = "3.15.1"

class SQLite(ConanFile):
	name = "SQLite"
	version = VERSION
	license = "Public domain, https://www.sqlite.org/copyright.html"
	url = "https://www.sqlite.org"
	settings = "os", "compiler", "arch", "build_type"
	generators = "cmake"
	exports = ["CMakeLists.txt"]
	description = """SQLite is an in-process library that implements a self-contained, serverless,
					zero-configuration, transactional SQL database engine."""
	
	def getInstallDir(self):
		return "install"
	
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
	
	def prepareDownload(self, url, label):
		self.output.info("")
		self.output.info("processing " + label + " ...")
		filename = os.path.basename(url)
		name = os.path.splitext(filename)[0]
		extension = os.path.splitext(filename)[1]
		return { "name": name, "filename": filename, "extension": extension }
	
	
	

	def __init__(self, *args, **kwargs):		
		self.sqlite3 = SQLite3Data(VERSION)
		super(SQLite, self).__init__(*args, **kwargs)
	
	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		zip_name = self.sqlite3.zip_name
		
		result = self.getIntoFolder("http://www.sqlite.org/2016/%s" % zip_name, self.name, False)
		
		os.rename("CMakeLists.txt", "%s/CMakeLists.txt" % result["name"])
		os.rename(result["name"], "src")

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
		
		opts = {"CMAKE_INSTALL_PREFIX": "install"}
		
		cmake.configure(defs=opts, source_dir=os.pardir, build_dir=os.path.join("src", "build"))
		
		cmake.build(target="install")

	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy("*", dst=".", src=os.path.join("src", "build", "install"))

	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.cpp_info.libs = ["sqlite3"]

class SQLite3Data(object):
	version_re = re.compile(r"^\d+\.\d+(\.\d+)?$")
	amalgamation = "amalgamation"  # amalgamation or autoconf

	def __init__(self, version):
		assert self.version_re.match(version), "Version {!r} does not match valid pattern.".format(version)
		self.version = version

	@property
	def version_number(self):
		vitems = self.version.split(".")
		ret = vitems[0]
		for it in vitems[1:] + ["0"]*(4-len(vitems)):
			ret += it.zfill(2)
		return ret

	@property
	def zip_name(self):
		return "sqlite-{amalgamation}-{version}.zip".format(amalgamation=self.amalgamation, version=self.version_number)

	@property
	def zip_folder(self):
		return self.zip_name.split(".zip", 1)[0]