# download conan if it does not already exist
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/conan.cmake")
	message(STATUS "downloading conan.cmake from https://github.com/memsharded/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_CURRENT_LIST_DIR}/conan.cmake")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/conan.cmake)

add_definitions(-DUNICODE)
add_definitions(-D_UNICODE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# this one is important
SET(CMAKE_SYSTEM_NAME Linux)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)



if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
elseif(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -std=c++0x -pthread -D__STDC_CONSTANT_MACROS")
	set(CMAKE_CXX_FLAGS	"${CMAKE_CXX_FLAGS} -DMACHINE_ARCH_ARM -fPIC -DLINUX=1 -UMMX")
else()
	message(FATAL_ERROR "only MSVC and GCC compilers are supported")
endif()

set(CONNECTED_VISION_CONAN_PACKAGES_DEFAULT
	Boost/1.58.0@covi/stable
#	FFmpeg/3.2.4@covi/stable
	libcurl/7.47.1@covi/stable
	OpenCV/3.1.0@covi/stable
	OpenSSL/1.0.2g@covi/stable
	POCO/1.6.1@covi/stable
	RapidJSON/1.0.2@covi/stable
	StackWalker/2014.12.28@covi/stable
	SQLite/3.15.1@covi/stable
	zlib/1.2.8@covi/stable
)



function(append_conan_packages_to_target_link_libraries_list packageNames result)
	foreach(packageName ${packageNames})
		list(APPEND ${result} "CONAN_PKG::${packageName}")
	endforeach()
	
	set(${result} ${${result}} PARENT_SCOPE)
endfunction()



function(create_version_info_file checkoutDir templateFile destinationFile)
	execute_process(COMMAND git log -1 --abbrev-commit WORKING_DIRECTORY "${checkoutDir}" OUTPUT_VARIABLE gitOutput)
	
	# read the version info template file
	file(READ "${templateFile}" template)
	
	if(gitOutput MATCHES "commit ([A-Za-z0-9]+).*")
		# extract the git hash from the git log command output
		string(REGEX REPLACE "GIT_COMMIT_HASH [^\r\n]+" "GIT_COMMIT_HASH \"${CMAKE_MATCH_1}\"" template "${template}" )
		
		# check for local modifications
		execute_process(COMMAND git diff-index --quiet HEAD -- WORKING_DIRECTORY "${checkoutDir}" RESULT_VARIABLE result)
		string(REGEX REPLACE "GIT_LOCAL_MODIFICATIONS [^\r\n]+" "GIT_LOCAL_MODIFICATIONS ${result}" template "${template}" )
	endif()
	
	# write the version info file
	file(WRITE "${destinationFile}" "${template}")
endfunction()



function(get_architecture_name result)
	if(MSVC)
		if(CMAKE_CL_64)
			set(temp x64)
		else()
			set(temp Win32)
		endif()
	else()
		# TODO: implement architecture name
	endif()
		
	set(${result} ${temp} PARENT_SCOPE)
endfunction()



function(get_bin_install_directory result)
	get_install_directory("bin" ${result})
	set(${result} ${${result}} PARENT_SCOPE)
endfunction()



function(get_compiler_short_name result)
	if(MSVC)
		string(REGEX REPLACE "Visual Studio [0-9]+ ([0-9]+) *.*" "\\1" temp ${CMAKE_GENERATOR})
		
		if(temp MATCHES ${CMAKE_GENERATOR})
			message(FATAL_ERROR "failed to extract compiler short name for MSVC compiler (CMAKE_GENERATOR: ${CMAKE_GENERATOR})")
		endif()
		
		set(temp "VS${temp}")
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		set(temp "GCC${CMAKE_CXX_COMPILER_VERSION}")
	else()
		message(FATAL_ERROR "unsupported compiler")
	endif()
	
	set(${result} ${temp} PARENT_SCOPE)
endfunction()



function(get_conan_variable name result)
	include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
	set(${result} ${${name}} PARENT_SCOPE)
endfunction()



function(get_install_directory outputType result)
	set(str "${outputType}")
		
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		get_compiler_short_name(compilerShortName)
		set(str "${str}/${compilerShortName}")
		
		get_architecture_name(achitecture)
		
		if(achitecture)
			set(str "${str}/${achitecture}")
		endif()
		
		if(MSVC)
			# info for install into configuration subdirectories: \${CMAKE_INSTALL_CONFIG_NAME} will be converted to e.g. Debug, Release, ... with MSVC, and to . otherwise
			set(str "${str}/\${CMAKE_INSTALL_CONFIG_NAME}")
		else()
			if(NOT CMAKE_BUILD_TYPE)
				set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
			endif()
			
			set(str "${str}/${CMAKE_BUILD_TYPE}")
		endif()
	endif()
	
	set(${result} ${str} PARENT_SCOPE)
endfunction()



function(get_lib_install_directory result)
	get_install_directory("lib" ${result})
	set(${result} ${${result}} PARENT_SCOPE)
endfunction()



function(get_lib_directory result)
	get_install_directory("lib" ${result})
	
	if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
		# specify the parent directory of the Debug/Release subdirectories as the link_directories command only accepts it that way
		if(MSVC)
			set(${result} "${${result}}/..")
		endif()
	else()
		set(${result} "${CMAKE_INSTALL_PREFIX}/${${result}}")
	endif()
	
	set(${result} ${${result}} PARENT_SCOPE)
endfunction()



function(execute_conan_cmake_run_without_targets)
	conan_cmake_run(REQUIRES
		${CONNECTED_VISION_CONAN_PACKAGES_DEFAULT}
		${ARGN}
		BASIC_SETUP
		BUILD
		outdated
	)
endfunction()



function(execute_conan_cmake_run_with_targets)
	conan_cmake_run(REQUIRES
		${CONNECTED_VISION_CONAN_PACKAGES_DEFAULT}
		${ARGN}
		BASIC_SETUP
		CMAKE_TARGETS
		BUILD
		outdated
	)
endfunction()
