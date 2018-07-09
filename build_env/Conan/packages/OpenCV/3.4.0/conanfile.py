from conans import ConanFile, CMake
import os, fnmatch

class OpenCVConan(ConanFile):
	# Description must be very short for conan.io
	description = "OpenCV: Open Source Computer Vision Library."
	name = "OpenCV"
	version = "3.4.0"
	opencv_version_suffix = "340"
	settings = "os", "compiler", "build_type", "arch"
	options = {
		"shared": [True, False],
		"with_1394":[True, False],
		"with_gtk": [True, False],
		"with_qt": [True, False],
		"with_openxl": [True, False],
		"with_ipp": [True, False],
		"with_itt": [True, False],
		"with_opengl": [True, False],
		"with_cuda": [True, False],
		"with_jpeg": [True, False],
		"build_jpeg": [True, False],
		"with_png": [True, False],
		"build_png": [True, False],
		"with_jasper": [True, False],
		"build_jasper": [True, False],
		"with_zlib": [True, False],
		"build_zlib": [True, False],
		"with_tiff": [True, False],
		"build_tiff": [True, False],
		"with_tbb": [True, False],
		"build_tbb": [True, False],
		"with_openexr": [True, False],
		"build_openexr": [True, False],
		"with_webp": [True, False],
		"build_webp": [True, False],
		"build_tests": [True, False],
		"build_perf_tests": [True, False],
		"build_opencv_apps": [True, False],
		"cpack_binary_nsis": [True, False],
		"build_opencv_calib3d": [True, False],
		"build_opencv_features2d": [True, False],
		"build_opencv_flann": [True, False],
		"build_opencv_highgui": [True, False],
		"build_opencv_imgcodecs": [True, False],
		"build_opencv_imgproc": [True, False],
		"build_opencv_ml": [True, False],
		"build_opencv_objectdetect": [True, False],
		"build_opencv_photo": [True, False],
		"build_opencv_shape": [True, False],
		"build_opencv_stitching": [True, False],
		"build_opencv_superres": [True, False],
		"build_opencv_ts": [True, False],
		"build_opencv_video": [True, False],
		"build_opencv_videoio": [True, False],
		"build_opencv_videostab": [True, False]
	}
	default_options = "shared=False",\
		"with_1394=False",\
		"with_gtk=False",\
		"with_qt=False",\
		"with_openxl=False",\
		"with_ipp=False",\
		"with_itt=False",\
		"with_opengl=False",\
		"with_cuda=False",\
		"with_jpeg=True",\
		"build_jpeg=True",\
		"with_png=True",\
		"build_png=True",\
		"with_jasper=True",\
		"build_jasper=True",\
		"with_zlib=True",\
		"build_zlib=True",\
		"with_tiff=True",\
		"build_tiff=True",\
		"with_tbb=False",\
		"build_tbb=False",\
		"with_openexr=True",\
		"build_openexr=True",\
		"with_webp=True",\
		"build_webp=True",\
		"build_tests=False",\
		"build_perf_tests=False",\
		"build_opencv_apps=False",\
		"cpack_binary_nsis=False",\
		"build_opencv_calib3d=True",\
		"build_opencv_features2d=True",\
		"build_opencv_flann=True",\
		"build_opencv_highgui=True",\
		"build_opencv_imgcodecs=True",\
		"build_opencv_imgproc=True",\
		"build_opencv_ml=True",\
		"build_opencv_objectdetect=True",\
		"build_opencv_photo=True",\
		"build_opencv_shape=True",\
		"build_opencv_stitching=True",\
		"build_opencv_superres=True",\
		"build_opencv_ts=True",\
		"build_opencv_video=True",\
		"build_opencv_videoio=True",\
		"build_opencv_videostab=True"
	url = "https://github.com/xmar/conan-opencv"
	license = "http://http://opencv.org/license.html"
	generators = "cmake"
	short_paths = True

	# def requirements(self):
		# self.output.info("")
		# self.output.info("---------- requirements ----------")
		# self.output.info("")
		
		# if self.settings.os == "Linux":
			# self.requires("zlib/1.2.11@covi/stable", private=False)
	
	def source(self):
		self.output.info("")
		self.output.info("---------- source ----------")
		self.output.info("")
		
		self.run("git clone https://github.com/opencv/opencv.git")
		self.run("cd opencv && git checkout tags/3.4.0")

	def build(self):
		self.output.info("")
		self.output.info("---------- build ----------")
		self.output.info("")
		self.output.info("os		: " + str(self.settings.os))
		self.output.info("arch	  : " + str(self.settings.arch))
		self.output.info("build_type: " + str(self.settings.build_type))
		
		cmake = CMake(self)
		cmake_options = {
			"CMAKE_INSTALL_PREFIX": "install",
			"WITH_1394": self.options.with_1394,
			"WITH_OPENXL": self.options.with_openxl,
			"WITH_IPP": self.options.with_ipp,
			"WITH_ITT": self.options.with_itt,
			"WITH_QT": self.options.with_qt,
			"WITH_GTK": self.options.with_gtk,
			"WITH_OPENGL": self.options.with_opengl,
			"WITH_CUDA": self.options.with_cuda,
			"WITH_JPEG": self.options.with_jpeg,
			"BUILD_JPEG": self.options.build_jpeg,
			"WITH_PNG": self.options.with_png,
			"BUILD_PNG": self.options.build_png,
			"WITH_JASPER": self.options.with_jasper,
			"BUILD_JASPER": self.options.build_jasper,
			"WITH_ZLIB": self.options.with_zlib,
			"BUILD_ZLIB": self.options.build_zlib,
			"WITH_TIFF": self.options.with_tiff,
			"BUILD_TIFF": self.options.build_tiff,
			"WITH_TBB": self.options.with_tbb,
			"BUILD_TBB": self.options.build_tbb,
			"WITH_OPENEXR": self.options.with_openexr,
			"BUILD_OPENEXR": self.options.build_openexr,
			"WITH_WEBP": self.options.with_webp,
			"BUILD_WEBP": self.options.build_webp,
			"BUILD_SHARED_LIBS": self.options.shared,
			"BUILD_TESTS": self.options.build_tests,
			"BUILD_PERF_TESTS": self.options.build_perf_tests,
			"BUILD_opencv_apps": self.options.build_opencv_apps,
			"CPACK_BINARY_NSIS": self.options.cpack_binary_nsis,
			"BUILD_opencv_calib3d": self.options.build_opencv_calib3d,
			"BUILD_opencv_features2d": self.options.build_opencv_features2d,
			"BUILD_opencv_flann": self.options.build_opencv_flann,
			"BUILD_opencv_highgui": self.options.build_opencv_highgui,
			"BUILD_opencv_imgcodecs": self.options.build_opencv_imgcodecs,
			"BUILD_opencv_imgproc": self.options.build_opencv_imgproc,
			"BUILD_opencv_ml": self.options.build_opencv_ml,
			"BUILD_opencv_objectdetect": self.options.build_opencv_objectdetect,
			"BUILD_opencv_photo": self.options.build_opencv_photo,
			"BUILD_opencv_shape": self.options.build_opencv_shape,
			"BUILD_opencv_stitching": self.options.build_opencv_stitching,
			"BUILD_opencv_superres": self.options.build_opencv_superres,
			"BUILD_opencv_ts": self.options.build_opencv_ts,
			"BUILD_opencv_video": self.options.build_opencv_video,
			"BUILD_opencv_videoio": self.options.build_opencv_videoio,
			"BUILD_opencv_videostab": self.options.build_opencv_videostab
		}

		if self.settings.compiler == "Visual Studio":
			cmake_options["BUILD_WITH_STATIC_CRT"] = self.settings.compiler.runtime in ["MT","MTd"]
		cmake.configure(defs=cmake_options, source_dir="opencv")
		cmake.build(target="install")

	def package(self):
		self.output.info("")
		self.output.info("---------- package ----------")
		self.output.info("")
		
		self.copy(pattern="*.h*", dst="include", src =os.path.join("install", "include"), keep_path=True)

		if self.settings.os == "Windows":
			self.copy(pattern="*.lib", dst="lib", src="3rdparty\\lib", keep_path=False)
			#self.copy(pattern="*.lib", dst="lib", src="3rdparty\\ippicv\\ippicv_win\\lib\\intel64", keep_path=False)
			self.copy(pattern="*.lib", dst="lib", src="install", keep_path=False)
			self.copy(pattern="*.dll", dst="bin", src="bin", keep_path=False)
			self.copy(pattern="*.exe", dst="bin", src="bin", keep_path=False)

		if self.settings.os == "Linux":
			self.copy(pattern="*.a", dst="lib", src="3rdparty/lib", keep_path=False)
			#self.copy(pattern="*.a", dst="lib", src="3rdparty/ippicv/ippicv_lnx/lib/intel64", keep_path=False)
			self.copy(pattern="*.a", dst="lib", src="install", keep_path=False)
			self.copy(pattern="*.so*", dst="lib", src="install", keep_path=False)

	def package_info(self):
		self.output.info("")
		self.output.info("---------- package_info ----------")
		self.output.info("")
		
		libs_opencv = [
			"opencv_calib3d",
			"opencv_flann",
			"opencv_highgui",
			"opencv_imgcodecs",
			"opencv_imgproc",
			"opencv_ml",
			"opencv_objdetect",
			"opencv_photo",
			"opencv_shape",
			"opencv_stitching",
			"opencv_superres",
			"opencv_video",
			"opencv_videoio",
			"opencv_videostab",
			"opencv_core" # GCC wants this last
		]
		libs_3rdparty = [
			"zlib",
			"libjpeg",
			"libpng",
			"libjasper",
			"libtiff",
			"libwebp",
			"IlmImf"
		]
		libs_win = [
			#"ippicvmt"
		]
		libs_linux = [
			#"ippicv",
			"pthread",
			"dl" # GCC wants this last
		]
		if self.settings.compiler == "Visual Studio":
			debug_suffix = ("d" if self.settings.build_type=="Debug" else "")
			libs_opencv_win = list(map(lambda n: n + self.opencv_version_suffix + debug_suffix, libs_opencv))
			libs_3rdparty_win = list(map(lambda n: n + debug_suffix, libs_3rdparty))
			libs = libs_opencv_win
			libs.extend(libs_3rdparty_win)
			self.cpp_info.libs.extend(libs)
		elif self.settings.compiler == "gcc":
			libs = libs_opencv
			libs.extend(libs_3rdparty)
			libs.extend(libs_linux)
			self.cpp_info.libs.extend(libs)

