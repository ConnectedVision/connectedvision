import fileinput
import os
import re
import sys
import shutil
import time
from conans import ConanFile, tools



class MSYS2(ConanFile):
	name = "MSYS2"
	version = "2016.10.25"
	license = "various, http://www.msys2.org"
	url = "http://www.msys2.org"
	settings = {"os": ["Windows"]}



	def checkMsysSetupFinished(self, logfile, token):
		try:
			for line in fileinput.input(logfile):
				if re.search(token, line):
					return True
		except:
			pass
		
		return False



	def countdown(self, t, message, abortCheckFunction=None):
		line = ""
		
		while t:
			mins, secs = divmod(t, 60)
			timeformat = "{:02d}:{:02d}".format(mins, secs)
			line = message + timeformat
			print(line, end="\r")
			time.sleep(1)
			t -= 1
			
			if abortCheckFunction:
				# additional waiting time when abort check function resolves to True
				if abortCheckFunction():
					t = 10
		
		print(" " * len(line), end="\r")



	def getEnvPathSuffix(self, rootDir):
		suffix = ""
		
		msysRootDirRelative = os.path.dirname(self.getMsysCmdFileRelative(rootDir))
		msysRootDirAbsolute = os.path.join(rootDir, msysRootDirRelative)
		suffix += ";" + msysRootDirAbsolute
		
		msysUsrBinDirRelative = os.path.join(msysRootDirRelative, "usr", "bin")
		msysUsrBinDirAbsolute = os.path.join(rootDir, msysUsrBinDirRelative)
		suffix += ";" + msysUsrBinDirAbsolute
		
		return suffix



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



	def getMsysCmdFileRelative(self, rootDir):
		msysFileRelative = os.path.join(self.name, "msys2_shell.cmd")
		msysFile = os.path.join(rootDir, msysFileRelative)
		
		if not os.path.exists(msysFile):
			raise Exception("failed to locate MSYS2 command file in " + msysFile)
		
		return msysFileRelative



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(f) ]



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
		
		url = "http://repo.msys2.org/distrib/i686/msys2-base-i686-20161025.tar.xz"
		self.getIntoFolder(url, self.name, False)
		
		dirnames = self.getSubdirectories(".")
		
		if len(dirnames) < 1:
			raise Exception("archive does not contain any subdirectories")
		
		os.rename(dirnames[0], self.name)



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
				
		rootDir = os.getcwd()
		
		# copy the directory from build dir to package dir
		cmdFile = self.getMsysCmdFileRelative(rootDir)
		cmdDirName = os.path.dirname(cmdFile)
		# self.copy does not copy empty directories which leads to problems when calling MSYS2 setup because of a missing /tmp directory
		# self.copy("*", dst=cmdDirName, src=cmdDirName)
		src = os.path.join(rootDir, cmdDirName)
		dst = os.path.join(self.package_folder, cmdDirName)
		shutil.copytree(src, dst)
		
		rootDir = self.package_folder
		
		# patch the MSYS2 command file in the package directory to be able to determine if the setup is finished by logging the console output to a file
		cmdFileAbsolute = self.getMsysCmdFileRelative(rootDir)
		cmdFileAbsolute = os.path.join(rootDir, cmdFileAbsolute)
		
		logfile = "temp.log"
		
		for line in fileinput.input(cmdFileAbsolute, inplace=True):
			line = re.sub(r"(-i /msys2.ico)", r"\1 -l tmp/" + logfile, line)
			sys.stdout.write(line)
			
		
		# set path environment variable to be able to call MSYS2 and pacman
		pathSuffix = self.getEnvPathSuffix(rootDir)
		os.environ["path"] += ";" + pathSuffix
		
		rootDir = os.path.join(rootDir, cmdDirName)
		cmdFile = os.path.basename(cmdFile)
		logfile = os.path.join(rootDir, "tmp", logfile)
		
		with tools.chdir(rootDir):
			self.run(cmdFile + " \"\"")
		
		# check if the MSYS2 setup finished
		self.countdown(120, "remaining grace period for MSYS2 setup: ", (lambda: self.checkMsysSetupFinished(logfile, "--> Installing /usr/share/info/which.info.gz ... done")))
		
		try:
			os.unlink(logfile)
		except:
			pass
		
		self.run("pacman --noconfirm -S make")
		self.run("pacman --noconfirm -S perl")
		self.run("pacman --noconfirm -S yasm")
		
		# create empty include directory to avoid Conan CMake error "Imported target [...] includes non-existent path [...] /include" when using this package in a CMake project
		os.makedirs(os.path.join(self.package_folder, "include"))



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		self.env_info.path.append(os.path.join(self.package_folder, self.name))
		self.env_info.path.append(os.path.join(self.package_folder, self.name, "usr", "bin"))