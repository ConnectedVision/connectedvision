import os
import platform
import shutil
from conans import ConanFile, tools



class NodeJs(ConanFile):
	name = "Node.js"
	version = "7.9.0"
	license = "https://raw.githubusercontent.com/nodejs/node/master/LICENSE"
	url = "https://nodejs.org"
	settings = {"os": ["Windows", "Linux"]}



	def getIntoFolder(self, url, label):
		result = self.prepareDownload(url, label)
		tools.download(url, result["filename"], retry=3, retry_wait=10)
		
		tempDir = os.path.abspath(os.path.join(os.getcwd(), os.pardir, os.pardir, "temp"))
		
		if os.path.exists(tempDir):
			try:
				shutil.rmtree(tempDir)
			except:
				if self.settings.os == "Windows":
					self.run("rmdir /q /s \"" + tempDir + "\"")
		
		tools.unzip(result["filename"], tempDir)
		
		dirs = self.getSubdirectories(tempDir)
		
		if(len(dirs) < 1):
			raise Exception("failed to extract source archive")
		
		srcDir = os.path.join(tempDir, dirs[0])
		os.rename(srcDir, self.name)
		
		shutil.rmtree(tempDir)
		os.unlink(result["filename"])
		
		return result



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(os.path.join(d, f)) ]



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
		
		url = "https://nodejs.org/dist/v" + self.version + "/node-v" + self.version + "-"
		
		archStr = ""
		
		if "64" in platform.architecture()[0]:
			archStr = "x64"
		else:
			archStr = "x86"
		
		if self.settings.os == "Windows":
			url += "win-" + archStr + ".zip"
		else:
			url += "linux-" + archStr + ".tar.gz"
		
		self.getIntoFolder(url, self.name)
		
		packagesCodeGenerator = [
			"chai",
			"mkpath",
			"node-uuid",
			"swig",
			"winston"
		]
		
		packagesSystemTest = [
			"async",
			"chai",
			"clone",
			"deep-diff",
			"extfs",
			"fs.extra",
			"is-my-json-valid",
			"joe",
			"joe-reporter-console",
			"node.extend",
			"optimist",
			"request",
			"request-json",
			"underscore"
		]
		
		packages = list()
		packages.extend(packagesCodeGenerator)
		packages.extend(packagesSystemTest)
		packages = list(set(packages))
		packages.sort()
		
		packageRootDir = self.name
		
		if self.settings.os == "Linux":
			packageRootDir = os.path.join(packageRootDir, "lib")
			os.environ["PATH"] = os.path.abspath(os.path.join(self.name, "bin")) + ":" + os.environ["PATH"]
		
		with tools.chdir(packageRootDir):
			for package in packages:
				self.run("npm install " + package)



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		# self.copy("*", src=self.name, dst="bin")

		# self.copy and the automatic build directory removal strategy from Conan upon rebuild lead to an error on Windows for paths longer than 255 characters
		# moving the data from the build directory to the package directory helps to avoid this problem
		# when the move operation is done within the package step, then this leads to a different error on Windows ("The file is a broken symlink") during the package step for file paths longer than 255 characters
		# the value of the self.build_folder variable is provided in the package_info step using a text file because the self.build_folder variable is not available in the package_info step (self.package_folder is available though)
		if self.settings.os == "Windows":
			with open(os.path.join(self.package_folder, "temp.txt"), "w") as f:
				f.write(self.build_folder)
		else:
			os.rename(os.path.join(self.build_folder, self.name), self.package_folder)



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		# create an empty include directory in order to avoid CMake errors when this package recipe is included in a CMakeLists.txt
		includeDir = os.path.join(self.package_folder, "include")
		
		if not os.path.exists(includeDir):
			os.makedirs(includeDir)
		
		binDir = os.path.join(self.package_folder, "bin")
		
		# workaround for behavior described in package step
		if self.settings.os == "Windows" and not os.path.exists(binDir):
			tempFile = os.path.join(self.package_folder, "temp.txt")
			
			with open(tempFile, "r") as f:
				buildDir = f.read()
				
			if len(buildDir) < 1 or not os.path.exists(buildDir):
				raise Exception("failed to obtain build_dir variable within package_info step")
			
			os.rename(os.path.join(buildDir, self.name), os.path.join(self.package_folder, "bin"))
			os.remove(tempFile)
		
		self.env_info.path.append(binDir)
		
		if self.settings.os == "Windows":
			self.env_info.NODE_PATH = os.path.join(binDir, "node_modules")
		else:
			self.env_info.NODE_PATH = os.path.join(self.package_folder, "lib", "node_modules")