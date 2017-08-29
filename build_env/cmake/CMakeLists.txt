cmake_minimum_required(VERSION 2.8.12)

project(ConnectedVision)

add_subdirectory(Core)
add_subdirectory(Modules/DirectoryIterator)
add_subdirectory(Modules/DummyBoundingBoxes)
add_subdirectory(Modules/FileExport)
add_subdirectory(Modules/FileImporter)
# add_subdirectory(Modules/RTPImporter)
add_subdirectory(Modules/SyntheticVideo)
add_subdirectory(Modules/ThumbnailGenerator)
# add_subdirectory(Modules/VideoImporter)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../../" CACHE PATH "default install path" FORCE)
endif()
