import argparse
import glob
import os
import platform
import shutil
import stat
import subprocess

parser = argparse.ArgumentParser(description="Connected Vision Swagger HTML/PDF doc generator")
parser.add_argument("-d", "--dir", help="Connected Vision module directory path (contains the def subdirectory with the module-, input- and output description", type=str, required=True)
args = parser.parse_args()

moduleDir = args.dir
scriptDir = os.path.dirname(os.path.realpath(__file__))

if not os.path.exists(moduleDir):
	raise Exception("the specified module directory does not exist: " + moduleDir)

swaggerJson = os.path.join(moduleDir, "def", "Swagger.json")

if not os.path.exists(swaggerJson):
	raise Exception("the Swagger JSON file does not exist: " + swaggerJson)

workingDir = os.path.join(moduleDir, "doc", "swagger2markup", "temp")

if os.path.exists(workingDir):
	shutil.rmtree(workingDir)

# template from https://github.com/Swagger2Markup/swagger2markup-gradle-project-template
shutil.copytree(os.path.join(scriptDir, "template"), workingDir)

if not os.path.exists(workingDir):
	raise Exception("failed to prepare Swagger2Markup working directory " + workingDir)

os.unlink(os.path.join(workingDir, "src", "docs", "swagger", "swagger_petstore.yaml"))

shutil.copyfile(swaggerJson, os.path.join(workingDir, "src", "docs", "swagger", "swagger.json"))

# replace the sample Swagger asciidoc with the asciidoc from the module directory
if os.path.exists(os.path.join(moduleDir, "doc", "swagger2markup", "asciidoc")):
	shutil.rmtree(os.path.join(workingDir, "src", "docs", "asciidoc"))
	shutil.copytree(os.path.join(moduleDir, "doc", "swagger2markup", "asciidoc"), os.path.join(workingDir, "src", "docs", "asciidoc"))

gradleFile = os.path.join(workingDir, "build.gradle")

with open(gradleFile) as f:
	content = f.read().replace("swagger_petstore.yaml", "swagger.json")

with open(gradleFile, "w") as f:
	f.write(content)

cmd = []

if platform.system() == "Windows":
	cmd.extend(["cmd", "/c", "gradlew.bat"])
else:
	cmd.append("./gradlew")
	
	# set gradlew executable permission
	gradle = os.path.join(workingDir, "gradlew")
	os.chmod(gradle, os.stat(gradle).st_mode | stat.S_IEXEC)

cmd.extend(["clean", "asciidoctor"])

returncode = subprocess.call(cmd, cwd = workingDir)

if returncode != 0:
	raise Exception("call to gradlew failed")

htmlBuildDir = os.path.join(workingDir, "build", "asciidoc", "html5")
pdfBuildDir = os.path.join(workingDir, "build", "asciidoc", "pdf")
docDirDst = os.path.join(moduleDir, "doc", "swagger2markup")

# copy possibly existing images for the HTML doc (not done by Swagger2Markup)
if os.path.exists(htmlBuildDir):
	imageDirSrc = os.path.join(workingDir, "src", "docs", "asciidoc")
	
	for ext in ["*.gif", "*.jpg", "*.jpeg", "*.png", "*.svg"]:
		for file in glob.iglob(os.path.join(imageDirSrc, ext)):
			shutil.copy2(file, htmlBuildDir)
	
	dstDir = os.path.join(docDirDst, "html")
	
	if os.path.exists(dstDir):
		shutil.rmtree(dstDir)
	
	shutil.copytree(htmlBuildDir, dstDir)

if os.path.exists(pdfBuildDir):
	dstDir = os.path.join(docDirDst, "pdf")
	
	if os.path.exists(dstDir):
		shutil.rmtree(dstDir)
	
	shutil.copytree(pdfBuildDir, dstDir)

shutil.rmtree(workingDir)
