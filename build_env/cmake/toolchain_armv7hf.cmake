set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
set(CMAKE_CXX_COMPILER_ID "GNU")

execute_process(COMMAND "${CMAKE_CXX_COMPILER}" ARGS "-v" ERROR_VARIABLE errorStr OUTPUT_QUIET)
string(REGEX MATCH "gcc version ([0-9\\.]+)" errorStr "${errorStr}")

if(NOT CMAKE_MATCH_1)
	message(FATAL_ERROR "failed to determine the compiler version when searching for \"gcc version\" in the output of the command \"${CMAKE_CXX_COMPILER} -v\"")
endif()

set(CMAKE_CXX_COMPILER_VERSION ${CMAKE_MATCH_1})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STDC_CONSTANT_MACROS -DMACHINE_ARCH_ARM -fPIC -DLINUX=1 -UMMX")

# indicate Conan to use C++11
# this may be required for cross compiling on x86 when the standard GCC compiler is also installed and the Conan compiler detection overrules the compiler.libcxx setting defined in the Conan profile replacing libstdc++11 with libstdc++ 
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.1")
	set(_GLIBCXX_USE_CXX11_ABI ON)
endif()
