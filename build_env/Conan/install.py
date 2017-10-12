import argparse
import os
import platform
import subprocess
import sys
import tools as customTools
import traceback
from conans import tools as conanTools



def installPackages():
	parser = argparse.ArgumentParser(description="Installer for for Conan packages. By default, i.e. if no command line arguments are specified, it only exports the Conan package recipes. If architectures and configs are specified, it also builds the packages for these settings.")
	parser.add_argument("-a", "--arch", help="system architectures", nargs="+", type=str, required=False, default=[""], choices=["x86", "x86_64"])
	parser.add_argument("-c", "--config", help="configurations", nargs="+", type=str, required=False, default=[""], choices=["Debug", "Release"])
	parser.add_argument("-r", "--remote", help="use remote package recipe from Conan package repository instead of exporting the local recipe", required=False, action="store_true")
	args = parser.parse_args()
	
	user = "covi"
	channel = "stable"
	
	packages = []
	
	if platform.system() == "Windows":
		packages.extend([
			"c99-to-c89/1.0.3",
			"MSYS2/2016.10.25"
		])
	
	packages.extend([
		"Boost/1.58.0",
		"CppUTest/3.8",
		"FFmpeg/3.2.4",
		"libcurl/7.47.1",
		"Node.js/7.9.0",
		"OpenCV/3.1.0",
		"OpenSSL/1.0.2g",
		"POCO/1.6.1",
		"RapidJSON/1.0.2",
		"SQLite/3.15.1",
		"StackWalker/2014.12.28",
		"zlib/1.2.8"
	])
	
	for package in packages:
		dirPathList = [os.path.join(os.getcwd(), "packages")] + package.split("/")
		dirPath = os.path.abspath(os.path.join(*dirPathList))
		
		with conanTools.chdir(dirPath):
			for a in args.arch:
				for c in args.config:
					runtime = ""
					
					if c == "Debug":
						runtime = "MDd"
					elif c == "Release":
						runtime = "MD"
					elif c:
						raise Exception("invalid configuration: " + c)
					
					name = package.split("/")[0]
					version = package.split("/")[1]
					installPackage(name, version, user, channel, a, c, runtime, args.remote)



def installPackage(name, version, user, channel, arch="", config="", runtime="", remote=False):
	if not remote:
		customTools.exportPackage(user, channel)
	
	# if no architecture or config were provided and the packe was exported (only possible for local package recipes) then return since the package recipe was exported to the Conan cache directory by the preceding command
	if not arch or not config:
		return
	
	reference = name + "/" + version + "@" + user + "/" + channel
	cmd = ["conan", "install", reference, "-b", "outdated", "-s", "arch=" + arch, "-s", "build_type=" + config, "-u"]
	
	if platform.system() == "Windows":
		cmd.extend(["-s", "compiler=Visual Studio", "-s", "compiler.runtime=" + runtime, "-g", "visual_studio"])
	else:
		cmd.extend(["-s", "compiler=gcc"])
	
	returncode = subprocess.call(cmd)
	
	if returncode != 0:
		raise Exception("conan install command failed:\n" + str(cmd))
	
	if platform.system() == "Windows":
		try:
			customTools.generateVisualStudioPropertySheet(arch, config, os.getcwd())
		except Exception:
			print("")
			print(traceback.format_exc())
			print("")



installPackages()