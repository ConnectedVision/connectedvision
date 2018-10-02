#!/usr/bin/env bash

import argparse
import os
import platform
import subprocess
import sys
import tools as customTools
import traceback



def installPackages():
	parser = argparse.ArgumentParser(description="Installer for for Conan packages. By default, i.e. if no command line arguments are specified, it only exports the local Conan package recipes to the Conan cache. If architectures and configs are specified, it also builds the packages for these settings.")
	parser.add_argument("-a", "--arch", help="system architectures", nargs="+", type=str, required=False, default=[""], choices=["x86", "x86_64"])
	parser.add_argument("-c", "--config", help="configurations", nargs="+", type=str, required=False, default=[""], choices=["Debug", "Release"])
	parser.add_argument("-r", "--remote", help="use remote package recipe from Conan package repository instead of exporting the local recipe", required=False, action="store_true")
	args = parser.parse_args()
	
	if args.remote and ((type(args.arch) is list and "" in args.arch) or (type(args.config) is list and "" in args.config)):
		raise Exception("when using the -r/--remote parameter, the specification of the -a/--arch and -c/--config parameters is mandatory")
	
	user = "covi"
	channel = "stable"
	
	packages = []
	
	if platform.system() == "Windows":
		packages.extend([
			"c99-to-c89/1.0.3",
			"MSYS2/2016.10.25",
			"StackWalker/2014.12.28"
		])
	else:
		packages.append("NASM/2.13.02")
	
	packages.extend([
		"zlib/1.2.11",
		"Boost/1.58.0",
		"CppUTest/3.8",
		"FFmpeg/3.2.4",
		"libcurl/7.47.1",
		"Node.js/7.9.0",
		"OpenCV/3.1.0",
		"OpenSSL/1.0.2g",
		"POCO/1.6.1",
		"RapidJSON/1.0.2",
		"SQLite/3.15.1"
	])
	
	for package in packages:
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
	# export recipe to the Conan cache using the local file instead of the file from the Connected Vision Conan repository on bintray.com
	if not remote:
		filePath = os.path.join(os.path.dirname(__file__), "packages", name, version, "conanfile.py")
		customTools.exportPackage(filePath, user, channel)
		
		# if no architecture or config were specified, then skip the Conan install step
		if not arch or not config:
			return
	
	reference = name + "/" + version + "@" + user + "/" + channel
	
	cmd = ["conan", "install", reference, "-u", "-b", "outdated", "-s", "arch=" + arch, "-s", "build_type=" + config]
	
	if platform.system() == "Windows":
		cmd.extend(["-s", "compiler=Visual Studio", "-s", "compiler.runtime=" + runtime, "-g", "visual_studio"])
	else:
		cmd.extend(["-s", "compiler=gcc"])
	
	# use check_call without try-except to raise an exception if the command fails and as a result terminate the execution of the parent installPackages() method
	subprocess.check_call(cmd, universal_newlines=True)
	
	if platform.system() == "Windows":
		try:
			customTools.generateVisualStudioPropertySheet(arch, config, os.getcwd())
		except Exception:
			print("")
			print(traceback.format_exc())
			print("")



if __name__ == "__main__":
	installPackages()