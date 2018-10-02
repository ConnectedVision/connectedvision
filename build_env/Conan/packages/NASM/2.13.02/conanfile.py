import os
from conans import ConanFile, AutoToolsBuildEnvironment, tools



class NASM(ConanFile):
	name = "NASM"
	version = "2.13.02"
	url = "http://www.nasm.us"
	settings = {"os": ["Linux"]}



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(f) ]



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		filename = "nasm-" + self.version + ".tar.bz2"
		url = "http://www.nasm.us/pub/nasm/releasebuilds/" + self.version + "/" + filename
		self.output.info("downloading " + url)
		tools.download(url, filename, retry=3, retry_wait=10)
		tools.unzip(filename, self.source_folder)

		dirnames = self.getSubdirectories(self.source_folder)
		
		if len(dirnames) < 1:
			raise Exception("archive does not contain any subdirectories")
		
		os.rename(dirnames[0], self.name)
		os.remove(filename)



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
			
		with tools.chdir(self.name):
			env = AutoToolsBuildEnvironment(self)
			env.configure(args=["--prefix=" + self.package_folder])
			env.make()
			env.make(args=["install"])



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))