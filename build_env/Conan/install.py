#!/usr/bin/env python3

import argparse
import os
import platform
import re
import subprocess
import tools as customTools



def installPackages():
	"""
	Installs the Conan packages of the Connected Vision dependencies (but not the Connected Vision Conan package itself).

	If --arch and --config are not specified, then only export package recipies to the Conan cache.
	Otherwise export the recipies to the Conan cache and build them using the specified build architecture and build config.

	If --remote is specfied, then the Conan Bintray repository is used as source for exporting the Conan package recipes.
	Otherwise, the recipes from the "packages" subdirectory are exported.
	"""
	
	parser = argparse.ArgumentParser(description="Installer for for Conan packages. By default, i.e. if no command line arguments are specified, it only exports the local Conan package recipes to the Conan cache. If architectures and configs are specified, it also builds the packages for these settings.")
	parser.add_argument("-a", "--arch", help="system architectures", nargs="+", type=str, required=False, default=[""], choices=["x86", "x86_64"])
	parser.add_argument("-c", "--config", help="configurations", nargs="+", type=str, required=False, default=[""], choices=["Debug", "Release"])
	parser.add_argument("-r", "--remote", help="use remote package recipe from Conan package repository instead of exporting the local recipe", required=False, action="store_true")
	args = parser.parse_args()
	
	if args.remote and ((isinstance(args.arch, list) and "" in args.arch) or (isinstance(args.config, list) and "" in args.config)):
		raise Exception("when using the -r/--remote parameter, the specification of the -a/--arch and -c/--config parameters is mandatory")
	
	packages = []
	
	if platform.system() == "Windows":
		packages.extend([
			"c99-to-c89",
			"MSYS2",
			"StackWalker"
		])
	else:
		packages.append("NASM")
	
	packages.extend([
		"zlib",
		"Boost",
		"CppUTest",
		"FFmpeg",
		"libcurl",
		"Node.js",
		"OpenCV",
		"OpenSSL",
		"POCO",
		"RapidJSON",
		"SQLite"
	])
	
	for package in packages:
		for a in args.arch:
			for c in args.config:
				installPackage(package, a, c, args.remote)
				
				

def installPackage(name, arch="", config="", remote=False):
	"""
	Installs a Conan package using the packages directory (not bintray.com) as source.
	
	Args:
		name: package name
		arch + config: architecture and build type (same as in installPackages())
	"""

	user = "covi"
	
	packageInfo = customTools.getPackageInfo(name)
	
	# export recipe to the Conan cache using the local file instead of the file from the Connected Vision Conan repository on bintray.com
	if not remote:
		customTools.exportPackage(packageInfo["filePath"], user, packageInfo["channel"])
		
		# if no architecture or config were specified, then skip the Conan install step
		if not arch or not config:
			return
	
	reference = name + "/" + packageInfo["version"] + "@" + user + "/" + packageInfo["channel"]
	
	cmd = ["conan", "install", reference, "-u", "-b", "outdated", "-s", "arch=" + arch, "-s", "build_type=" + config]
	
	if platform.system() == "Windows":
		runtime = ""
		
		if config == "Debug":
			runtime = "MDd"
		elif config == "Release":
			runtime = "MD"
		elif config:
			raise Exception("invalid configuration: " + config)
				
		cmd.extend(["-s", "compiler=Visual Studio", "-s", "compiler.runtime=" + runtime, "-g", "visual_studio"])
	else:
		cmd.extend(["-s", "compiler=gcc"])
	
	# use check_call without try-except to raise an exception if the command fails and as a result terminate the execution of the parent installPackages() method
	subprocess.check_call(cmd, universal_newlines=True)
	


if __name__ == "__main__":
	installPackages()
