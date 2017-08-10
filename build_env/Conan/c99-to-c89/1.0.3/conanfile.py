import os
from conans import ConanFile, tools



class C99ToC89(ConanFile):
	name = "c99-to-c89"
	version = "1.0.3"
	license = "Apache License 2.0, https://github.com/libav/c99-to-c89/blob/master/LICENSE"
	url = "https://github.com/libav/c99-to-c89"
	settings = {"os": ["Windows"]}



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



	def getNameVersion(self):
		return "c99-to-c89-1.0.3"



	def prepareDownload(self, url, label):
		self.output.info("")
		self.output.info("processing " + label + " ...")
		filename = os.path.basename(url)
		name = os.path.splitext(filename)[0]
		extension = os.path.splitext(filename)[1]
		return { "name": name, "filename": filename, "extension": extension }



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		
		url = "https://github.com/libav/c99-to-c89/releases/download/release-1.0.3/c99-to-c89-1.0.3.zip"

		self.getIntoFolder(url, self.name, True)



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
				
		self.copy("*", dst="bin", src=self.getNameVersion())
		
		# create empty include directory to avoid Conan CMake error "Imported target [...] includes non-existent path [...] /include" when using this package in a CMake project
		os.makedirs(os.path.join(self.package_folder, "include"))



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.env_info.path.append(os.path.join(self.package_folder, "bin"))