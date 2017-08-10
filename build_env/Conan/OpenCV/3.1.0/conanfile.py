import ast
import glob
import os
import re
import shutil
from conans import CMake, ConanFile, tools



class OpenCV(ConanFile):
	name = "OpenCV"
	version = "3.1.0"
	license = "3-clause BSD License, http://opencv.org/license.html"
	url = "http://opencv.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64"], "build_type": ["Debug", "Release"]}
	exports = "CMakeLists.txt"
	options = {
		"BUILD_DOCS": [True, False],
		"BUILD_EXAMPLES": [True, False],
		"BUILD_JASPER": [True, False],
		"BUILD_JPEG": [True, False],
		"BUILD_PERF_TESTS": [True, False],
		"BUILD_PNG": [True, False],
		"BUILD_TESTS": [True, False],
		"BUILD_TIFF": [True, False],
		"BUILD_WEBP": [True, False],
		"ENABLE_AVX": [True, False],
		"ENABLE_AVX2": [True, False],
		"ENABLE_FMA3": [True, False],
		"ENABLE_SSE": [True, False],
		"ENABLE_SSE2": [True, False],
		"ENABLE_SSE3": [True, False],
		"ENABLE_SSE41": [True, False],
		"ENABLE_SSE42": [True, False],
		"ENABLE_SSSE3": [True, False],
		"WITH_1394": [True, False],
		"WITH_AVFOUNDATION": [True, False],
		"WITH_CARBON": [True, False],
		"WITH_CLP": [True, False],
		"WITH_CSTRIPES": [True, False],
		"WITH_CUBLAS": [True, False],
		"WITH_CUDA": [True, False],
		"WITH_CUFFT": [True, False],
		"WITH_DIRECTX": [True, False],
		"WITH_EIGEN": [True, False],
		"WITH_FFMPEG": [True, False],
		"WITH_GDAL": [True, False],
		"WITH_GIGEAPI": [True, False],
		"WITH_GPHOTO2": [True, False],
		"WITH_GSTREAMER": [True, False],
		"WITH_GSTREAMER_0_10": [True, False],
		"WITH_GTK": [True, False],
		"WITH_GTK_2_X": [True, False],
		"WITH_INTELPERC": [True, False],
		"WITH_IPP": [True, False],
		"WITH_IPP_A": [True, False],
		"WITH_JASPER": [True, False],
		"WITH_JPEG": [True, False],
		"WITH_MATLAB": [True, False],
		"WITH_MSMF": [True, False],
		"WITH_NVCUVID": [True, False],
		"WITH_OPENCL": [True, False],
		"WITH_OPENCLAMDBLAS": [True, False],
		"WITH_OPENCLAMDFFT": [True, False],
		"WITH_OPENCL_SVM": [True, False],
		"WITH_OPENEXR": [True, False],
		"WITH_OPENGL": [True, False],
		"WITH_OPENMP": [True, False],
		"WITH_OPENNI": [True, False],
		"WITH_OPENNI2": [True, False],
		"WITH_PNG": [True, False],
		"WITH_PVAPI": [True, False],
		"WITH_QT": [True, False],
		"WITH_QUICKTIME": [True, False],
		"WITH_TBB": [True, False],
		"WITH_TIFF": [True, False],
		"WITH_UNICAP": [True, False],
		"WITH_VA": [True, False],
		"WITH_VA_INTEL": [True, False],
		"WITH_VTK": [True, False],
		"WITH_WEBP": [True, False],
		"WITH_XIMEA": [True, False],
		"WITH_XINE": [True, False]
	}
	default_options = '''
BUILD_DOCS=False
BUILD_EXAMPLES=False
BUILD_JASPER=True
BUILD_JPEG=True
BUILD_PERF_TESTS=False
BUILD_PNG=True
BUILD_TESTS=False
BUILD_TIFF=True
BUILD_WEBP=True
ENABLE_AVX=False
ENABLE_AVX2=False
ENABLE_FMA3=True
ENABLE_SSE=True
ENABLE_SSE2=True
ENABLE_SSE3=True
ENABLE_SSE41=True
ENABLE_SSE42=False
ENABLE_SSSE3=True
WITH_1394=False
WITH_AVFOUNDATION=False
WITH_CARBON=False
WITH_CLP=False
WITH_CSTRIPES=False
WITH_CUBLAS=False
WITH_CUDA=False
WITH_CUFFT=False
WITH_DIRECTX=False
WITH_EIGEN=False
WITH_FFMPEG=False
WITH_GDAL=False
WITH_GIGEAPI=False
WITH_GPHOTO2=False
WITH_GSTREAMER=False
WITH_GSTREAMER_0_10=False
WITH_GTK=False
WITH_GTK_2_X=False
WITH_INTELPERC=False
WITH_IPP=False
WITH_IPP_A=False
WITH_JASPER=True
WITH_JPEG=True
WITH_MATLAB=False
WITH_MSMF=False
WITH_NVCUVID=False
WITH_OPENCL=True
WITH_OPENCLAMDBLAS=False
WITH_OPENCLAMDFFT=False
WITH_OPENCL_SVM=False
WITH_OPENEXR=False
WITH_OPENGL=False
WITH_OPENMP=False
WITH_OPENNI2=False
WITH_OPENNI=False
WITH_PNG=True
WITH_PVAPI=False
WITH_QT=False
WITH_QUICKTIME=False
WITH_TBB=False
WITH_TIFF=True
WITH_UNICAP=False
WITH_VA=False
WITH_VA_INTEL=False
WITH_VTK=False
WITH_WEBP=True
WITH_XIMEA=False
WITH_XINE=False
'''
	
	
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



	def getInstallDir(self):
		return os.path.join(self.name, "build", "install")



	def getSubdirectories(self, d):
		return [ f for f in os.listdir(d) if os.path.isdir(f) ]



	def prepareDownload(self, url, label):
		self.output.info("")
		self.output.info("processing " + label + " ...")
		filename = os.path.basename(url)
		name = os.path.splitext(filename)[0]
		extension = os.path.splitext(filename)[1]
		return { "name": name, "filename": filename, "extension": extension }



	def requirements(self):
		self.output.info("")
		self.output.info("---------- requirements ----------")
		self.output.info("")
		
		if self.settings.os == "Linux":
			self.requires("zlib/1.2.8@covi/stable", private=False)



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://github.com/opencv/opencv/archive/" + self.version + ".zip"
		
		self.getIntoFolder(url, self.name, False)
		
		dirnames = self.getSubdirectories(".")
		
		if len(dirnames) < 1:
			raise Exception("archive does not contain any subdirectories")
		
		os.rename(dirnames[0], self.name)



	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		
		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		
		# create options dict for CMake command
		opts = dict()
		
		# extract the options dict from the options variable in order to append additional values
		for item in self.options.items():
			opts[item[0]] = item[1]
		
		opts["BUILD_SHARED_LIBS"] = False
		opts["INSTALL_CREATE_DISTRIB"] = True
		
		if self.settings.os == "Linux":
			opts["OPENCV_BUILD_3RDPARTY_LIBS"] = False
			opts["BUILD_ZLIB"] = False
			
			zlibRootDir = self.deps_cpp_info["zlib"].rootpath
			opts["ZLIB_INCLUDE_DIR"] = os.path.join(zlibRootDir, self.deps_cpp_info["zlib"].includedirs[0])
			
			libDir = os.path.join(zlibRootDir, self.deps_cpp_info["zlib"].libdirs[0])
			libFiles = [filename for filename in os.listdir(libDir) if re.match("^(lib)?" + self.deps_cpp_info["zlib"].libs[0] + r"\.(a|lib)", filename)]
			
			if not libFiles:
				raise Exception("zlib (Conan package, not the OpenCV 3rdparty version) was not found in: " + libDir)
			
			opts["ZLIB_LIBRARY"] = os.path.join(libDir, libFiles[0])
		
		if self.settings.compiler == "Visual Studio":
			if self.settings.compiler.runtime == "MT" or self.settings.compiler.runtime == "MTd":
				opts["BUILD_WITH_STATIC_CRT"] = True
			else:
				opts["BUILD_WITH_STATIC_CRT"] = False
		
		opts["CMAKE_INSTALL_PREFIX"] = os.path.basename(self.getInstallDir())
		
		cmake = CMake(self)
		
		buildDir = os.path.join(self.name, "build")
		
		os.makedirs(buildDir)
		
		cmake.configure(defs=opts, source_dir=os.pardir, build_dir=buildDir)
		
		cmake.build(target="install")



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		installDir = self.getInstallDir()
		findRootDir = installDir
		
		if self.settings.os == "Linux":
			findRootDir = os.path.join(findRootDir, "share", "OpenCV")
		
		shutil.move("CMakeLists.txt", findRootDir)
		
		buildDir = os.path.join(findRootDir, "temp")
		
		os.makedirs(buildDir)
		
		cmake = CMake(self)
		
		cmake.configure(source_dir=os.pardir, build_dir=buildDir)
		
		variablesFile = os.path.join(findRootDir, "variables.txt")

		if not os.path.isfile:
			raise Exception("expected CMake find script output file does not exist: " + variablesFile)

		variables = ast.literal_eval(open(variablesFile, "r").read())
		
		includeDirsStr = variables["includeDirs"]
		includeDirs = includeDirsStr.split(";")
		includeDir = os.path.abspath(min(includeDirs, key=len))
		
		libDirsStr = variables["libDir"]
		libDirs = libDirsStr.split(";")
		libDir = min(libDirs, key=len)

		if self.settings.os == "Linux":
			libs = variables["libs"].split(";")

			libsSubsetOrdered = ["opencv_imgproc", "opencv_core"]

			for lib in libsSubsetOrdered:
				if lib in libs:
					libs.remove(lib)
					libs.append(lib)

			with tools.chdir(libDir):
				libs3rdparty = [os.path.splitext(lib)[0].replace("lib", "", 1) for lib in glob.glob("*.a")]
				variables["libs"] = ";".join(libs) + ";" + ";".join(libs3rdparty) + ";z"

			open(variablesFile, "w").write(str(variables))
			
			libDirLinux = os.path.join(installDir, "lib")
			self.copy("*", src=libDirLinux, dst="lib")
		
		self.copy("*", src=includeDir, dst="include")
		self.copy("*", src=libDir, dst="lib")
		self.copy("variables.txt", src=findRootDir, dst=".")



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libDir = os.path.join(self.package_folder, self.cpp_info.libdirs[0])
		
		with tools.chdir(libDir):
			if self.settings.os == "Windows":
				self.cpp_info.libs = glob.glob("*.lib")
			else:
				variablesFile = os.path.join(self.package_folder, "variables.txt")
				variables = ast.literal_eval(open(variablesFile, "r").read())
				
				self.cpp_info.libs = variables["libs"].split(";")