import os
import shutil
from conans import ConanFile, tools

class StackWalker(ConanFile):
	name = "StackWalker"
	version = "2014.12.28"
	license = "New BSD License (BSD), https://stackwalker.codeplex.com/license"
	url = "https://stackwalker.codeplex.com"
	exports = ["stackwalker-2014-12-28.zip"]

	def getZipName(self):
		return "stackwalker-2014-12-28.zip"
	
	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		# tools.download("http://download-codeplex.sec.s-msft.com/Download/Release?ProjectName=stackwalker&DownloadId=1354904&FileTime=130642377182300000&Build=21046", self.getZipName())
		tools.unzip(self.getZipName())
		os.unlink(self.getZipName())
		
		os.makedirs("src")
		shutil.copy(os.path.join(os.path.join("Main", self.name), self.name + ".cpp"), "src")
		shutil.copy(os.path.join(os.path.join("Main", self.name), self.name + ".h"), "src")
		
		shutil.rmtree("Main")

	def package(self):
		self.copy("*", dst="include", src="src")

	def build(self):
		pass