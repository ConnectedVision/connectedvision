import glob
import os
import re
import subprocess
from conans import CMake, ConanFile, tools



class OpenCV(ConanFile):
	name = "OpenCV"
	version = "3.4.3"
	license = "3-clause BSD License, http://opencv.org/license.html"
	url = "http://opencv.org"
	settings = {"os": ["Windows", "Linux"], "compiler": ["Visual Studio", "gcc"], "arch": ["x86", "x86_64", "armv7hf"], "build_type": ["Debug", "Release"]}
	exports = ["VideoIO_CMakeLists.txt.patch"]
	options = {
		"BUILD_DOCS": [True, False],
		"BUILD_EXAMPLES": [True, False],
		"BUILD_JASPER": [True, False],
		"BUILD_JPEG": [True, False],
		"BUILD_opencv_apps": [True, False],
		"BUILD_opencv_extra": [True, False],
		"BUILD_PERF_TESTS": [True, False],
		"BUILD_PNG": [True, False],
		"BUILD_TESTS": [True, False],
		"BUILD_TIFF": [True, False],
		"BUILD_ZLIB": [True, False],
		"OPENCV_PYTHON_SKIP_DETECTION": [True, False],
		"WITH_1394": [True, False],
		"WITH_CLP": [True, False],
		"WITH_CSTRIPES": [True, False],
		"WITH_CUBLAS": [True, False],
		"WITH_CUDA": [True, False],
		"WITH_CUFFT": [True, False],
		"WITH_DIRECTX": [True, False],
		"WITH_DSHOW": [True, False],
		"WITH_EIGEN": [True, False],
		"WITH_FFMPEG": [True, False],
		"WITH_GDAL": [True, False],
		"WITH_GIGEAPI": [True, False],
		"WITH_GPHOTO2": [True, False],
		"WITH_GSTREAMER": [True, False],
		"WITH_GSTREAMER_0_10": [True, False],
		"WITH_GTK": [True, False],
		"WITH_GTK_2_X": [True, False],
		"WITH_IMGCODEC_HDR": [True, False],
		"WITH_IMGCODEC_SUNRASTER": [True, False],
		"WITH_IMGCODEC_PXM": [True, False],
		"WITH_INF_ENGINE": [True, False],
		"WITH_INTELPERC": [True, False],
		"WITH_IPP": [True, False],
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
		"WITH_OPENVX": [True, False],
		"WITH_PNG": [True, False],
		"WITH_PVAPI": [True, False],
		"WITH_PROTOBUF": [True, False],
		"WITH_QT": [True, False],
		"WITH_TBB": [True, False],
		"WITH_TIFF": [True, False],
		"WITH_UNICAP": [True, False],
		"WITH_VA": [True, False],
		"WITH_VA_INTEL": [True, False],
		"WITH_VFW": [True, False],
		"WITH_VTK": [True, False],
		"WITH_WEBP": [True, False],
		"WITH_XIMEA": [True, False],
		"WITH_XINE": [True, False],
		"WITH_ZLIB": [True, False]
	}
	default_options = {
		"BUILD_DOCS": False,
		"BUILD_EXAMPLES": False,
		"BUILD_JASPER": True,
		"BUILD_JPEG": True,
		"BUILD_opencv_apps": False,
		"BUILD_opencv_extra": False,
		"BUILD_PERF_TESTS": False,
		"BUILD_PNG": True,
		"BUILD_TESTS": False,
		"BUILD_TIFF": True,
		"BUILD_ZLIB": False,
		"OPENCV_PYTHON_SKIP_DETECTION": True,
		"WITH_1394": False,
		"WITH_CLP": False,
		"WITH_CSTRIPES": False,
		"WITH_CUBLAS": False,
		"WITH_CUDA": False,
		"WITH_CUFFT": False,
		"WITH_DIRECTX": False,
		"WITH_DSHOW": False,
		"WITH_EIGEN": False,
		"WITH_FFMPEG": True,
		"WITH_GDAL": False,
		"WITH_GIGEAPI": False,
		"WITH_GPHOTO2": False,
		"WITH_GSTREAMER": False,
		"WITH_GSTREAMER_0_10": False,
		"WITH_GTK": False,
		"WITH_GTK_2_X": False,
		"WITH_IMGCODEC_HDR": True,
		"WITH_IMGCODEC_SUNRASTER": True,
		"WITH_IMGCODEC_PXM": True,
		"WITH_INF_ENGINE": False,
		"WITH_INTELPERC": False,
		"WITH_IPP": False,
		"WITH_JASPER": True,
		"WITH_JPEG": True,
		"WITH_MATLAB": False,
		"WITH_MSMF": False,
		"WITH_NVCUVID": False,
		"WITH_OPENCL": True,
		"WITH_OPENCLAMDBLAS": False,
		"WITH_OPENCLAMDFFT": False,
		"WITH_OPENCL_SVM": False,
		"WITH_OPENEXR": False,
		"WITH_OPENGL": False,
		"WITH_OPENMP": False,
		"WITH_OPENNI2": False,
		"WITH_OPENVX": False,
		"WITH_OPENNI": False,
		"WITH_PNG": True,
		"WITH_PVAPI": False,
		"WITH_PROTOBUF": True,
		"WITH_QT": False,
		"WITH_TBB": False,
		"WITH_TIFF": True,
		"WITH_UNICAP": False,
		"WITH_VA": False,
		"WITH_VA_INTEL": False,
		"WITH_VFW": False,
		"WITH_VTK": False,
		"WITH_WEBP": True,
		"WITH_XIMEA": False,
		"WITH_XINE": False,
		"WITH_ZLIB": True
	}



	def download(self, url, filename="", dst="", subdir=False, sha256=""):
		"""
		Downloads an archive file from the specified URL, optionaly compares its SHA256 to the specified value and extracts the archive.
		
		Args:
		- url: source URL
		- filename: destination filename. If empty, then the filename is derived from the part after the last slash of the url.
		- dst: destination directory. If empty, then a directory name derived from the download link is used.
		- subdir: If False and the archive contains only a single root directory, then the content of that directory is extracted into the destination directory.
		- sha256: The expected SHA256 hash of the downloaded file to be compared to the actual file hash. If empty, then the check is omitted.
		"""
		
		self.output.info("")
		self.output.info("downloading " + url + " ...")
		
		if not filename:
			filename = os.path.basename(url)
		
		extension = os.path.splitext(filename)[1]
		
		if not self.settings.os == "Linux" or not tools.which("aria2c"):
			tools.download(url, filename, retry=3, retry_wait=10)
		else:
			self.run("aria2c -x 16 -s 16 " + url)
		
		if sha256:
			sha256File = tools.sha256sum(filename)
			
			if sha256.upper() != sha256File.upper():
				raise Exception("SHA256 of downloaded file (" + sha256File.upper() + ") does not match expected value (" + sha256.upper() + ")")
		
		self.output.info("SHA256 of downloaded file matches expected value (" + sha256.upper() + ")")
		
		if not dst:
			dst = os.path.join(os.getcwd(), self.name)
		
		self.output.info("extracting " + filename + " ...")
		
		if extension == ".xz":
			tools.untargz(filename, dst)
		else:
			tools.unzip(filename, dst)
		
		print("")
		
		content = os.listdir(dst)
		
		if not subdir and len(content) == 1 and os.path.isdir(os.path.join(dst, content[0])):
			tempDir = os.path.join(os.path.dirname(dst), self.name + "Temp")
			os.rename(os.path.join(dst, content[0]), tempDir)
			
			if os.path.isdir(dst):
				os.rmdir(dst)
			
			os.rename(tempDir, dst)
		
		os.remove(filename)
	
	
	
	def requirements(self):
		self.output.info("")
		self.output.info("---------- requirements ----------")
		self.output.info("")
		
		if self.options.WITH_FFMPEG == "True":
			self.requires("FFmpeg/4.1@covi/2.4.0", private=False)
		
		if not self.options.BUILD_ZLIB:
			self.requires("zlib/1.2.11@covi/2.3.0", private=False)



	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		url = "https://github.com/opencv/opencv/archive/" + self.version + ".zip"
		self.download(url, filename="opencv-3.4.3.zip", sha256="37C7D8C3B9807902AD11B9181BBDE61DCB3898A78A563130494752F46FE8CC5F")

		if self.options.BUILD_opencv_extra:
			url = "https://github.com/opencv/opencv_contrib/archive/" + self.version + ".zip"
			self.download(url, filename="opencv_contrib-3.4.3.zip", sha256="0F5472FD05ADD4538C45C91AF8320FF2D9B901BDFE000CD3A593E3A0A2890C48", dst=os.path.join(self.source_folder, "opencv_contrib"))


	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os        : " + str(self.settings.os))
		self.output.info("arch      : " + str(self.settings.arch))
		self.output.info("compiler  : " + str(self.settings.compiler) + " " + str(self.settings.compiler.version))
		self.output.info("build type: " + str(self.settings.build_type))

		if self.settings.compiler == "Visual Studio":
			self.output.info("runtime   : " + str(self.settings.compiler.runtime))
		else:
			self.output.info("libcxx    : " + str(self.settings.compiler.libcxx))
		
		# create options dict for CMake command
		opts = dict()
		
		# extract the options dict from the options variable in order to append additional values
		for item in self.options.items():
			opts[item[0]] = item[1]
		
		# not included in conan options since it has not been implemented/tested
		opts["BUILD_SHARED_LIBS"] = "False"
		opts["INSTALL_CREATE_DISTRIB"] = "True"
		
		# use already existing conan zlib package
		if opts["BUILD_ZLIB"] == "False":
			zlibRootDir = self.deps_cpp_info["zlib"].rootpath
			opts["ZLIB_INCLUDE_DIR"] = os.path.join(zlibRootDir, self.deps_cpp_info["zlib"].includedirs[0])
			
			libDir = os.path.join(zlibRootDir, self.deps_cpp_info["zlib"].libdirs[0])
			
			libFiles = [filename for filename in os.listdir(libDir) if re.match("^(lib)?" + self.deps_cpp_info["zlib"].libs[0] + r"\.(a|lib)", filename)]
			
			if not libFiles:
				raise Exception("zlib (Conan package, not the OpenCV 3rdparty version) was not found in: " + libDir)
			
			opts["ZLIB_LIBRARY"] = os.path.join(libDir, libFiles[0])
			
			# replace backslash path separators for Windows with forward slashes to avoid linker problems with unknown escape sequences
			if self.settings.os == "Windows":
				opts["ZLIB_LIBRARY"] = opts["ZLIB_LIBRARY"].replace("\\", "/")
		
		if opts["WITH_FFMPEG"] == "True":
			# generate a CMake file for the find_package method
			cmd = ["conan", "install", "FFmpeg/4.1@covi/2.4.0", "-s", "build_type=" + str(self.settings.build_type)]
			
			if self.settings.compiler == "Visual Studio":
				cmd.extend(["-s", "compiler.runtime=" + str(self.settings.compiler.runtime)])
			else:
				cmd.extend(["-s", "compiler.libcxx=" + str(self.settings.compiler.libcxx)])
				
			cmd.extend(["-g", "cmake_find_package"])
			
			subprocess.check_call(cmd)
			
			r = re.compile(r"find.*ffmpeg.*\.cmake", re.I)
			
			# determine the path of the generated file
			ffmpegFindFile = [f for f in os.listdir(self.build_folder) if os.path.isfile(f) and r.match(f)]
			
			if not ffmpegFindFile:
				raise Exception("failed to generate FFmpeg find script for building OpenCV")
			
			ffmpegFindFileSrc = ffmpegFindFile[0]
			
			contentPrefix = ""			
			
			# add additional variables expected by OpenCV to the FindFFmpeg file
			for lib in self.deps_cpp_info["FFmpeg"].libs:
				contentPrefix += "SET(FFMPEG_"
				
				if self.settings.os == "Linux":
					contentPrefix += "lib"
				
				contentPrefix += lib + "_FOUND True)\n"
			
			with open(ffmpegFindFileSrc, "r+") as f:
				content = f.read()
				content = contentPrefix + re.sub("FFmpeg_", "FFMPEG_", content)
				
				f.seek(0)
				f.write(content)
				f.truncate()
			
			opts["OPENCV_FFMPEG_USE_FIND_PACKAGE"] = "FFmpeg"
			os.rename(ffmpegFindFileSrc, "FFmpegConfig.cmake")
			opts["FFmpeg_DIR"] = self.build_folder

			# OpenCV 3.4.3 with FFmpeg on Windows is only supported using the prebuilt FFmpeg DLL from OpenCV
			# integrating the static libs from the Conan package requires some adaptions
			if self.settings.compiler == "Visual Studio":
				cmd = ["git", "apply", "--ignore-space-change", "--whitespace=nowarn", os.path.join(self.build_folder, "VideoIO_CMakeLists.txt.patch")]
				subprocess.check_call(cmd, cwd=os.path.join(self.name, "modules", "videoio"))

				with open(os.path.join(self.name, "modules", "videoio", "src", "cap_ffmpeg_impl.hpp"), "r+") as f:
					content = f.read()
					f.seek(0)
					f.truncate()
					f.write(content.replace("st->avg_frame_rate = (AVRational){frame_rate, frame_rate_base};", "st->avg_frame_rate = AVRational{frame_rate, frame_rate_base};"))
		
		if self.settings.compiler == "Visual Studio":
			opts["BUILD_WITH_STATIC_CRT"] = self.settings.compiler.runtime in ["MT", "MTd"]
		
		if self.options.BUILD_opencv_extra:
			extraModulesDir = os.path.join(self.build_folder, "opencv_contrib", "modules")
			
			if not os.path.isdir(extraModulesDir):
				raise Exception("OpenCV extra modules (opencv_contrib) was not found @ " + extraModulesDir + ". Try removing and re-downloading sources again before rebuilding by calling conan conan remove -s " + self.name + "/" + self.version + "@" + self.user + "/" + self.channel)
			
			opts["OPENCV_EXTRA_MODULES_PATH"] = os.path.join(self.build_folder, "opencv_contrib", "modules")

		opts["CMAKE_INSTALL_PREFIX"] = "install"

		buildDir = os.path.join(self.name, "build")

		cmake = CMake(self)
		cmake.configure(defs=opts, source_folder=self.name, build_folder=buildDir)
		cmake.build(target="install")



	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		installDir = os.path.join(self.name, "build", "install")

		self.copy(pattern="*.h*", dst="include", src=os.path.join(installDir, "include"), keep_path=True)
		
		self.copy(pattern="**/CMakeVars.txt", keep_path=False)
		
		if self.settings.os == "Windows":
			self.copy(pattern="*.lib", dst="lib", src=installDir, keep_path=False)
		else:
			self.copy(pattern="*.a", dst="lib", src=installDir, keep_path=False)



	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libDir = os.path.join(self.package_folder, self.cpp_info.libdirs[0])
		
		if self.settings.os == "Windows":
			with tools.chdir(libDir):
				self.cpp_info.libs = glob.glob("*.lib")
			
			with open("CMakeVars.txt", "r", errors="ignore") as f:
				r = re.compile("HAVE_VFW=(.*)")
				vfwFlag = False
			
				for line in f.readlines():
					m = r.match(line)
					
					if m and m.group(1).lower() == "true":
						vfwFlag = True
				
				if vfwFlag:
					self.cpp_info.libs.append("Vfw32")
		else:
			with tools.chdir(libDir):
				libsAllUnsorted = libsAllUnsorted = glob.glob("*.a")
			
			# separate OpenCV libs from 3rd-party libs
			libsCv = []
			libs3rd = []
			r = re.compile(r"lib(opencv_.*)\.a")

			for lib in libsAllUnsorted:
				if r.match(lib):
					libsCv.append(r.match(lib).group(1))
				else:
					libs3rd.append(re.match(r"lib(.*)\.a", lib).group(1))
			
			# essential OpenCV libs which need to be at the end of the (OpenCV lib) list
			libsCvSubsetSorted = ["opencv_tracking", "opencv_dnn", "opencv_imgproc", "opencv_core"]

			for lib in libsCvSubsetSorted:
				if lib in libsCv:
					libsCv.remove(lib)
					libsCv.append(lib)
			
			# move OpenCV libs to the beginning of the list and 3rd-party libs to the end
			self.cpp_info.libs = libsCv + libs3rd
