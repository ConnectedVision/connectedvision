# Connected Vision

## Build on Windows (x86/x86_64) with Visual Studio:
1. install [Git](https://git-scm.com/download/win)
2. install [CMake](https://cmake.org/download) (version >= 3.0.0)
3. install [Python](https://www.python.org/downloads/windows) including `pip`
4. `pip install conan` (from console with administrator rights)
5. `conan search`
6. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
7. build the Connected Vision Conan package
	
	either explicitly by executing `conan install ConnectedVision/0.0.1@covi/stable -b outdated`
	
	or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build on Linux (x86/x86_64) with GCC:
1. `sudo apt-get install git`
2. `sudo apt-get install build-essential`
3. `sudo apt-get install cmake` (version >= 3.0.0)
4. `sudo apt-get install python-pip`
	
	`sudo pip install --upgrade pip` (only necessary if pip is already installed but too old)
5. `sudo pip install conan`
	
	`sudo pip install setuptools` (only necessary if a corresponding Conan error occurs)
6. `conan search`
7. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
8. build the Connected Vision Conan package
	
	either explicitly by executing `conan install ConnectedVision/0.0.1@covi/stable -b outdated`
	
	or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build on Linux (x86/x86_64) with GCC for armv7hf:

The cross-compilation described in the following was tested with the [Raspberry Pi GCC 4.9.3 toolchain](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/).

1. execute [native Linux build](#build-on-linux-x86x86_64-with-gcc) steps 1-7
2. copy the [armv7hf Conan profile template](build_env/Conan/profiles/armv7hf) file to the Conan profiles directory `$HOME/.conan/profiles`
3. update the `compiler.version` variable in the `settings` section and the `CC` and `CXX` variables in the `env` section of the armv7hf Conan profile to point to the full file path of your cross compiler, e.g. to the checkout of [[...]/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc) and [.../arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++), respectively
4. `conan config set general.default_profile=armv7hf`
5. copy the [CMake toolchain file](build_env/cmake/toolchain_armv7hf.cmake), e.g. to the checkout of the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer)
6. update the `CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER` variables of the CMake toolchain file accordingly (similar to step 3)
7. build the Connected Vision Conan package using the updated CMake toolchain file from step 6
	
	either explicitly by executing `conan install ConnectedVision/0.0.1@covi/stable -b outdated -o ConnectedVision:toolchain=<path/of/toolchain_armv7hf.cmake>`
	
	or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake) and building it using `cmake [...] -DCMAKE_TOOLCHAIN_FILE=<path/of/toolchain_armv7hf.cmake>`

## Build tested with...
OS                  | OS architecture | compiler                | compiler version | host architecture
---                 | ---             | ---                     | ---              | ---
Windows 7           | x86_64          | MSVC (Visual Studio)    | 10.0 (2010)      | x86 & x86_64
Windows 10          | x86_64          | MSVC (Visual Studio)    | 14.0 (2015)      | x86_64
Ubuntu 12.04 LTS    | x86_64          | GCC                     | 4.6.3            | x86_64
Ubuntu 12.04 LTS    | x86_64          | arm-linux-gnueabihf-gcc | 4.6.3            | armv7hf
Ubuntu Server 14.04 | x86_64          | GCC                     | 4.8.4            | x86_64
Linux Mint 17.3     | x86             | GCC                     | 4.8.4            | x86
Linux Mint 17.3     | x86_64          | GCC                     | 4.8.4            | x86_64
Linux Mint 17.3     | x86_64          | arm-linux-gnueabihf-gcc | 4.9.3            | armv7hf
Linux Mint 18.1     | x86_64          | GCC                     | 5.4.0            | x86_64
Linux Mint 18.2     | x86_64          | GCC                     | 5.4.0            | x86_64
Raspbian 4.9        | armv7hf         | GCC                     | 6.3.0            | armv7hf
