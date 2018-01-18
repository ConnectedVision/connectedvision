from conans import ConanFile

class RapidJSONConan(ConanFile):
	name = "RapidJSON"
	version = "1.0.2"
	license = "MIT, https://github.com/miloyip/rapidjson/blob/master/license.txt"
	url = "https://github.com/miloyip/rapidjson/"

	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		self.run("git clone https://github.com/miloyip/rapidjson")
		self.run("cd rapidjson && git checkout v%s" % self.version)

	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy("*", dst="include", src="rapidjson/include")

	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")