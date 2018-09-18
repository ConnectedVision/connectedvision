cmake_minimum_required(VERSION 2.8.12)

project(ConnectedVisionUnitTest)

option(USE_INSTALL_SUBDIRECTORY_STRUCTURE "create a subdirectory structure for the install directory which consists of architecture and configuration type" OFF)

set(ConnectedVisionCppRoot ../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

set(packages 
	CppUTest/3.8@covi/stable
	libcurl/7.47.1@covi/stable
)

execute_conan_cmake_run_without_targets(${packages})
execute_conan_cmake_run_with_targets(${packages})

set(ConnectedVisionUnitTestHeaders
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_DataHandling.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_IDataAllocator.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_Store_SQLite.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/MixIn_IDataAllocator.h
	${ConnectedVisionCppRoot}/test/UnitTest/MixIn_IStore.h
	${ConnectedVisionCppRoot}/test/UnitTest/Store_Null.h
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_StoreEnvironment.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_Module.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_Threads_Windows.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_Threads_Linux.hpp
	${ConnectedVisionCppRoot}/test/UnitTest/TestHelper_Threads.hpp
)

set(ConnectedVisionUnitTestSources
	${ConnectedVisionCppRoot}/test/UnitTest/Test_ModuleBaseClass.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_ModuleInputPins.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Sample.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_SmartPointer.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Ringbuffer.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/main.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_DataAllocator_Pool.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_DataAllocator_Primitive.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_SQLite.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_Pool.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Ringbuffer_Factory.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_SQLite_GeneratedObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_AliasID.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_Ringbuffer_Pool.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_SQLite_Basic.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_SQLite_Pool.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_Ringbuffer_GeneratedObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_SQLite_GeneratedObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Manager_Dynamic.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_Cache.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Store_Null.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Store_SQLite_Cache_generic_status.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_HTTP_ServerPoco.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Generic_status.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_OutputPin_JSON.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_Thread.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_ConfigList.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_ThreadSafe_Queue.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_CallStack.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_DynamicParameters.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_ConfigPreprocessor.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_GeneratedObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/MixIn_IDataAllocator.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/MixIn_IStore.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_RapidJSON.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/Test_WorkerController.cpp	
)

set(ConnectedVisionUnitTestGeneratedHeaders
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Store_SQLite_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Class_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Class_UnitTest_GeneratorTestCode_complexObject.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Class_UnitTest_GeneratorTestCode_objArray.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Class_UnitTest_GeneratorTestCode_simpleObject.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/Store_Manager_SQLite_UnitTest_GeneratorTestCode.h
)

set(ConnectedVisionUnitTestGeneratedSources

)

set(ConnectedVisionUnitTestGeneratedStubHeaders
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_SQLite_Stub_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_complexObject.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_objArray.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_simpleObject.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_SQLite_UnitTest_GeneratorTestCode_Default.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_SQLite_UnitTest_GeneratorTestCode_Default.h
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_Default.h
)

set(ConnectedVisionUnitTestGeneratedStubSources
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_SQLite_Stub_UnitTest_GeneratorTestCode.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_complexObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_objArray.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Stub_UnitTest_GeneratorTestCode_simpleObject.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode.cpp
	${ConnectedVisionCppRoot}/test/UnitTest/generated/stubs/Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode.cpp	
)

set(PlatformSpecificSources)

if(MSVC)
	get_conan_variable("CONAN_INCLUDE_DIRS_STACKWALKER" StackWalkerIncludeDir)
	set(PlatformSpecificSources ${StackWalkerIncludeDir}/StackWalker.cpp)
endif()

set(HEADERS
	${ConnectedVisionUnitTestHeaders}
	${ConnectedVisionUnitTestGeneratedHeaders}
	${ConnectedVisionUnitTestGeneratedStubHeaders}
)

set(SOURCES
	${ConnectedVisionUnitTestSources}
	${ConnectedVisionUnitTestGeneratedSources}
	${ConnectedVisionUnitTestGeneratedStubSources}
	${PlatformSpecificSources}
)


source_group(Source\ Files\\generated FILES
	${ConnectedVisionUnitTestGeneratedHeaders}
	${ConnectedVisionUnitTestGeneratedSources}
)

source_group(Source\ Files\\generated\\stubs FILES
	${ConnectedVisionUnitTestGeneratedStubHeaders}
	${ConnectedVisionUnitTestGeneratedStubSources}
)
	
include_directories(
	${ConnectedVisionCppRoot}/core/include
	${ConnectedVisionCppRoot}/core/src
)

if(NOT USE_CORE_AS_SUBPROJECT)
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
	endif()
	
	get_lib_directory(LibDirectory)
	
	if(NOT IS_ABSOLUTE ${LibDirectory})
		set(LibDirectory "${ConnectedVisionCppRoot}/${LibDirectory}")
	endif()
	
	link_directories(${LibDirectory})
endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(USE_CORE_AS_SUBPROJECT)
	add_subdirectory(../Core Core)
endif()

target_link_libraries(${PROJECT_NAME}
	ConnectedVisionCore
	CONAN_PKG::Boost
	CONAN_PKG::CppUTest
	CONAN_PKG::libcurl
	CONAN_PKG::OpenCV
	CONAN_PKG::POCO
	CONAN_PKG::SQLite
)

if(MSVC)
	# set startup project
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

if(USE_CORE_AS_SUBPROJECT AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()

get_bin_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})
