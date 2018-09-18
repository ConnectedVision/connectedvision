import os
import platform
import re
import shutil
import subprocess
import sys


# conditionally import modules and define methods based on the installed Python version
if sys.version_info > (3, 0, 0):
	import urllib.request
		
	def compareRecipeWithBintray():
		"""
		Compares the recipe from the current checkout with the recipe hosted on Bintray and throws an exception if a mismatch was detected.
		Differences regarding newline encoding (LF vs. CRLF) are deliberatly ignored.
		This method is supposed to be used by the build server for detecting mismatches between the two instances of the same recipe when accidentally not updating one of the two recipe storage locations.
		"""
		
		rootDir = os.path.join(os.getcwd(), "packages")
		
		for packageName in [d for d in os.listdir(rootDir) if os.path.isdir(os.path.join(rootDir, d))]:
			packageDir = os.path.join(rootDir, packageName)
			
			for packageVersion in [d for d in os.listdir(packageDir) if os.path.isdir(packageDir)]:
				recipeCheckoutFilePath = os.path.join(packageDir, packageVersion, "conanfile.py")
				
				if not os.path.exists(recipeCheckoutFilePath):
					continue
				
				with open(recipeCheckoutFilePath, "r") as f:
					recipeCheckoutContent = f.read()
				
				# make sure that line endings are LF
				recipeCheckoutContent = recipeCheckoutContent.replace("\r\n", "\n")
				
				url = "https://dl.bintray.com/covi/ConnectedVision/covi/" + packageName + "/" + packageVersion + "/stable/export/conanfile.py"
				
				try:
					with urllib.request.urlopen(url) as response:
						encoding = response.headers.get_content_charset("utf-8")
						recipeBintrayContent = response.read().decode(encoding)
				except:
					print("\nerror: failed to obtain Conan package recipe " + packageName + " " + packageVersion + " from " + url + "\n")
					raise
				
				# make sure that line endings are LF
				recipeBintrayContent = recipeBintrayContent.replace("\r\n", "\n")
				
				s = "comparing " + packageName + " " + packageVersion + " ... "
				
				if(recipeCheckoutContent != recipeBintrayContent):
					print(s + "ERROR")
					raise Exception("Conan package recipe " + packageName + " " + packageVersion + " from checkout does not match recipe on Bintray")
				
				print(s + "OK")



def compareRecipesWithCache(diffTool=""):
	"""
	Compares the recipes from the current repository checkout with the exported recipes of the Conan cache.
	
	The result of the comparison is displayed on the console:
	* cache != checkout: if the cell is marked with an x, then the recipe from the Conan cache and does not match the one from the Git checkout
	* checkout != HEAD: if the cell is marked with an x, then the recipe of the Git checkout does not match the one from the Git HEAD revision
	* package name
	* package version
	
	Additionally to the console output, it is attempted to visualize the differences using a diff tool installed on the current OS.
	
	Args:
		diffTool (str, optional): The path of the difftool to use. If omitted, then it is attempted to extract the diff tool from the Git configuration.
	"""
	
	import tempfile
	
	if sys.version_info > (3, 3, 0):
		from shutil import which
	else:
		from distutils.spawn import find_executable as which
	
	# if no valid diff tool was specified, then try to extract one from the Git configuration
	if not diffTool or not (os.path.exists(diffTool) or which(diffTool)):
		if diffTool:
			print("the specified diff tool was not found: \"" + diffTool + "\"")
		
		print("trying to extract a diff tool from the Git configuration ...")
		
		try:
			output = subprocess.check_output(["git", "config", "diff.tool"], universal_newlines=True)
			diffToolName = output.rstrip()
			output = subprocess.check_output(["git", "config", "difftool." + diffToolName + ".cmd"], universal_newlines=True)
			
			m = re.match(r"^[\"']?([^\"']+)[\"']?(?= [\"']?[\/\-\$](?:\w+)[\"']?[ $])", output)
			
			diffToolGit = m.group(1)
			
			if "\\\\" in diffToolGit:
				diffToolGit = diffToolGit.replace("\\ ", " ")
			
			diffToolGit = diffToolGit.replace("\\\\", "\\")
		except:
			pass
		
		if diffToolGit and (os.path.exists(diffToolGit) or which(diffToolGit)):
			print("located diff tool candidate: \"" + diffToolGit + "\"")
			diffTool = diffToolGit
		else:
			print("failed to locate diff tool candidate: \"" + diffToolGit + "\"")
			diffTool = ""
		
	if platform.system() == "Windows":
		homeEnvVar = "USERPROFILE"
	
	else:
		homeEnvVar = "HOME"
	
	if not homeEnvVar in os.environ:
		raise Exception("failed to determine the user home directory using the " + homeEnvVar + " environment variable")
	
	conanDataDir = os.path.join(os.environ[homeEnvVar], ".conan", "data")
	repoPackagesRoot = os.path.join(os.path.dirname(os.path.realpath(__file__)), "packages")
	repoRoot = os.path.abspath(os.path.join(repoPackagesRoot, os.pardir, os.pardir, os.pardir))
	
	n1 = 10
	f1 = "{:^" + str(n1) + "}"
	n2 = n1
	f2 = "{:^" + str(n2) + "}"
	n3 = 20
	f3 = "{:^" + str(n3) + "}"
	f3d = "{:<" + str(n3) + "}"
	n4 = 12
	f4 = "{:^" + str(n4) + "}"
	f4d = "{:<" + str(n4) + "}"
	
	print("")
	print(f1.format("cache") + "|" + f2.format("checkout") + "|" + f3.format("") + "|" + f4.format(""))
	print(f1.format("!=") + "|" + f2.format("!=") + "|" + f3.format("name") + "|" + f4.format("version"))
	print(f1.format("checkout") + "|" + f2.format("HEAD") + "|" + f3.format("") + "|" + f4.format(""))
	print(str("{:-^" + str(n1 + n2 + n3 + n4 + 3) + "}").format(""))
	
	for name in os.listdir(repoPackagesRoot):
		nameDir = os.path.join(repoPackagesRoot, name)
		
		if not os.path.isdir(nameDir):
			continue
		
		for version in os.listdir(nameDir):
			repoFile = os.path.join(repoPackagesRoot, name, version, "conanfile.py")
			cacheFile = os.path.join(conanDataDir, name, version, "covi", "stable", "export", "conanfile.py")
		
			if not os.path.exists(repoFile):
				raise Exception("something is wrong with this comparison script")
		
			if not os.path.exists(cacheFile):
				continue
		
			with open(repoFile, "r") as f:
						repoFileContent = f.read()
			
			with open(cacheFile, "r") as f:
						cacheFileContent = f.read()
		
			repoFileRelative = os.path.relpath(repoFile, repoRoot)
			cmd = ["git", "diff", "--quiet", "--exit-code", "HEAD", repoFileRelative]
			exitCode = subprocess.call(cmd, universal_newlines=True, cwd=repoRoot)
			
			if repoFileContent == cacheFileContent:
				if exitCode == 0:
					v1 = " "
					v2 = " "
				else:
					v1 = " "
					v2 = "x"
					
					if diffTool:
						subprocess.call(["git", "difftool", repoFileRelative], universal_newlines=True, cwd=repoRoot)
			else:
				if exitCode == 0:
					v1 = "x"
					v2 = " "
					
					if diffTool:
						os.system("\"" + diffTool + "\" " + cacheFile + " " + repoFile)
				else:
					v1 = "x"
					v2 = "x"
					
					if diffTool:
						with tempfile.NamedTemporaryFile(delete=True) as f:
							tf = f.name + ".txt"
							
							# replace backslashes with forward slashes as the Git command below would not work otherwise (at least for Git 2.18.0 on Windows 10)
							repoFileRelativeSlash = repoFileRelative.replace("\\", "/")
							
							os.system("git show HEAD:" + repoFileRelativeSlash + " > \"" + tf + "\" && \"" + diffTool + "\" \"" + tf + "\" " + cacheFile + " " + repoFile)
			
			print(f1.format(v1) + "|" + f2.format(v2) + "|" + f3d.format(" " + name) + "|" + f4d.format(" " + version))



def deleteDirectory(dirPath, message):
	# check if the package directory exists
	if not os.path.isdir(dirPath) or not os.path.exists(dirPath):
		return
	
	print(message + ": " + dirPath)
	
	try:
		shutil.rmtree(dirPath)
	except:
		# if shutil.rmtree failed (which sometimes happens on Windows) then try to use the Windows rmdir command
		if platform.system() == "Windows":
			os.system("rmdir /q /s \"" + dirPath + "\"")



def deleteCacheDirectories(exportCommandOutput):
	"""
	Workaround to explicitly delete the build and package directories from the Conan cache (and not just mark them as "deprecated" as Conan does) when the package recipe has changed.
	
	Args:
		exportCommandOutput: console output as (multi line) string from Conan export command
	"""
	
	# check if a new conanfile.py file was exported
	p = re.compile("^([^/]+/[^@]+@[^/]+/[^:]+): A new conanfile.py version was exported.*")
	
	for line in exportCommandOutput.splitlines():
		m = p.match(line)
		
		if m and m.group(1):
			packageReference = m.group(1)
			break
	
	# extract the recipe export directory
	p = re.compile(".* Folder: (.*)$")
	
	for line in exportCommandOutput.splitlines():
		m = p.match(line)
		
		if m and m.group(1):
			exportDir = m.group(1)
			break
	
	exportDir = ""
	
	if not m or not m.group(1):
		return
	
	exportDir = m.group(1)
	
	# check if the export directory candidate exists
	if not exportDir or not os.path.isdir(exportDir) or not os.path.exists(exportDir):
		return
	
	rootDir, foldername = os.path.split(exportDir)
	
	# check if the name of the export directory candidate is in fact export
	if foldername != "export":
		return
	
	deleteDirectory(os.path.join(rootDir, "package"), "deleting outdated package directory")
	deleteDirectory(os.path.join(rootDir, "build"), "deleting outdated build directory")



def exportPackage(packagePath, user, channel):
	cmd = ("conan export -k " + packagePath + " " + user + "/" + channel).split(" ")
	
	# it sometimes occurred that a previously exported recipe and other files in the Conan cache export directory were empty (file size zero) on a Linux Jenkins installation
	# trying to execute the Conan export command in such a case raised an exception
	# deleting the export directory from the Conan cache before executing the export command solved the problem
	if "CONAN_USER_HOME" in os.environ:
		p = packagePath
		
		if os.path.isfile(p):
			p = os.path.dirname(p)
		
		version = os.path.basename(p)
		
		p = os.path.abspath(os.path.join(p, os.pardir))
		
		package = os.path.basename(p)
		
		dst = os.path.join(os.environ["CONAN_USER_HOME"], ".conan", "data", package, version, user, channel, "export", "conanfile.py")
		
		if(os.path.exists(dst) and os.stat(dst).st_size == 0):
			print("deleting export directory because it contains an empty conanfile.py which would lead to problems when trying to call conan export for that package recipe (at least using Linux Conan 1.7.3)")
			
			try:
				shutil.rmtree(os.path.dirname(dst))
				print(" ... succeeded")
			except:
				print(" ... failed")
				pass
	
	try:
		output = subprocess.check_output(cmd, universal_newlines=True)
	except subprocess.CalledProcessError as e:
		print(e.output)
		raise e
	
	print(output)
	
	deleteCacheDirectories(str(output))



def generateVisualStudioPropertySheet(arch, config, srcDir):
	"""Visual Studio property sheet generator. It reads property sheets generated by Conan for one specific combination of system architecture and configuration (e.g. x86 Debug) and merges them in a single multi-config property sheet.")

	Args:
		arch: list of system architectures ["x86", "x86_64"]
		config: list of configurations ["Debug", "Release"]
		srcDir: parent directory of the conanbuildinfo.props property sheet generated by Conan
	"""
	
	import warnings
	import xml.etree.ElementTree as ET
	
	if not os.path.exists(srcDir):
		raise Exception("parent directory of property sheet does not exist: \"" + srcDir + "\"")
	
	src = os.path.join(srcDir, "conanbuildinfo.props")
	dst = os.path.join(srcDir, "multi.props")
	
	if not os.path.exists(src):
		warnings.warn("skipping multi-config property sheet generation since source property sheet does not exist: \"" + src + "\"")
		return
	
	archVs = ""
	
	if arch == "x86":
		archVs = "Win32"
	elif arch == "x86_64":
		archVs = "x64"
	else:
		raise Exception("invalid architecture: " + arch)
	
	namespaces = { "default": "http://schemas.microsoft.com/developer/msbuild/2003" }
	
	ET.register_namespace("", namespaces["default"])
	
	srcTree = ET.parse(src)
	srcRoot = srcTree.getroot()
	
	if not os.path.exists(dst):
		dstRoot = ET.Element("Project", {"ToolsVersion": "4.0"})
		tree = ET.ElementTree(dstRoot)
	else:
		tree = ET.parse(dst)
		dstRoot = tree.getroot()
	
	condition = "'$(Platform)|$(Configuration)'=='" + archVs + "|" + config + "'"
	
	dstNode = dstRoot.findall("default:ItemDefinitionGroup[@Condition=\"" + condition + "\"]", namespaces)
	
	if len(dstNode) > 0:
		dstRoot.remove(dstNode[0])
		
	nodes = srcRoot.findall("default:ItemDefinitionGroup", namespaces)
	
	if len(nodes) < 1:
		raise Exception("failed to find ItemDefinitionGroup in property sheet generated by Conan")
	
	srcNode = nodes[0]
	srcNode.set("Condition", condition)
	dstRoot.append(srcNode)
	
	tree.write(dst, encoding="utf-8", xml_declaration=True)
	
	# delete the source property sheet build artifact
	# for a situation of a failing subsequent build this measure is supposed to avoid accidental reuse of the wrong property sheet with possibly the wrong architecture
	os.remove(src)