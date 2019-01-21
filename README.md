# Connected Vision

## Build on Windows (x86/x86_64) with Visual Studio
1. install [Git](https://git-scm.com/download/win)
2. install [CMake](https://cmake.org/download) (3.x)
3. install [Python](https://www.python.org/downloads/windows) (3.x) including `pip3`
4. `pip3 install conan` (from console with administrator rights)
5. `conan search`
6. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
7. build the Connected Vision Conan package
	
	- either explicitly by executing `conan install ConnectedVision/2.4.0-rc.1@covi/stable -b outdated`
	
	- or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build on Linux (x86/x86_64) with GCC
1. `sudo apt-get install git`
2. `sudo apt-get install build-essential`
3. `sudo apt-get install cmake` (CMake 3.x required)
4. `python3 --version` (verify that Python 3.x is installed)
5. `sudo apt-get install python3-pip`
	
	`sudo pip3 install --upgrade pip` (only necessary if a corresponding error occurs)
5. `sudo pip3 install conan`
	
	`sudo pip3 install --upgrade setuptools` (only necessary if a corresponding error occurs)
6. `conan search`
7. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
8. build the Connected Vision Conan package
	
	- either explicitly by executing `conan install ConnectedVision/2.4.0-rc.1@covi/stable -b outdated`
	
	- or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build on Linux (x86/x86_64) with GCC for armv7hf

The cross-compilation described in the following was tested with the [Raspberry Pi GCC 4.9.3 toolchain](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/).

1. execute [native Linux build](#build-on-linux-x86x86_64-with-gcc) steps 1-7
2. copy the [armv7hf Conan profile template](build_env/Conan/profiles/armv7hf) file to the Conan profiles directory `$HOME/.conan/profiles`
3. update the `compiler.version` variable in the `settings` section and the `CC` and `CXX` variables in the `env` section of the armv7hf Conan profile to point to the full file path of your cross compiler, e.g. to the checkout of [[...]/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc) and [.../arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++](https://github.com/raspberrypi/tools/tree/master/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++), respectively
4. `conan config set general.default_profile=armv7hf`
5. copy the [CMake toolchain file](build_env/cmake/toolchain_armv7hf.cmake), e.g. to the checkout of the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer)
6. update the `CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER` variables of the CMake toolchain file accordingly (similar to step 3)
7. build the Connected Vision Conan package using the updated CMake toolchain file from step 6
	
	either explicitly by executing `conan install ConnectedVision/2.4.0-rc.1@covi/stable -b outdated -o ConnectedVision:toolchain=<path/of/toolchain_armv7hf.cmake>`
	
	or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake) and building it using `cmake [...] -DCMAKE_TOOLCHAIN_FILE=<path/of/toolchain_armv7hf.cmake>`

## Build tested with
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

## Build issues
### Build failes after updating Conan itself
After updating an existing Conan installation using `pip install conan -U` projects are failing to build with errors about Conan stating the correct usage of its command line parameters.
E.g. `[...] Conan executing: conan install [...]` `[...] ERROR: Exiting with code: [...]` `[...] usage: conan install [...]`

This may be due to a mismatch between the installed Conan version and the conan.cmake file. The conan.cmake file contains CMake build helpers required for using Conan from within CMake. conan.cmake is not provided by the Conan installation but (in general) needs to be downloaded seperately. In CMake projects the conan.cmake file can be obtained using the `file(DOWNLOAD "https://[...]` function, as it is done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/blob/master/DemoServer/build/cmake/CMakeLists.txt).

Try to replace the existing file with a version from [GitHub](https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake) that matches your Conan installation.

### Failing rebuild of a Conan package
It might occur that the build of a Conan package fails or is manually interrupted. When trying to execute the build again, it may happen that Conan is unable to delete the build or package directories of the preceding build attempt. If it then tries to create files or directories which already exist, it fails with the following errors:
```
ERROR: [WinError 183] Cannot create a file when that file already exists:
'C:\\Users\\auto\\.conan\\data\\PackageX\\1.0\\\covi\\channelY\\build\\1234567890abcdef1234567890abcdef1234567'
```
```
ERROR: [WinError 145] The directory is not empty:
'C:\\Users\\auto\\.conan\\data\\PackageX\\1.0\\covi\\channelY\\package\\1234567890abcdef1234567890abcdef1234567'
```
 
Manually delete both the corresponding build and package directories and restart the build.

### Build errors on Windows for Conan packages with long paths
On Windows there are different limits regarding the maximum directory and file path length. These limits depend on the method which is used to create/rename/delete files or directories. Calling `mkdir` or `rmdir` from the command line for directory paths longer than 248 characters fails. Extracting a zip archive with a deeper directory structure works, but handling those existing directory structures afterwards causes problems. This fuzzy behavior regarding path lengths may sometimes result in misleading errors  such as the following:
```
ERROR: The file is a broken symlink, verify that you are packaging the needed destination files:
'C:\\Users\\auto\\.conan\\data\\PackageX\\1.0\\covi\\channelY\\package\\1234567890abcdef1234567890abcdef1234567\\[..]\\path\\with\\more\\than\\250\\characters.txt'
```
If rebuilding the Conan package does not work, then manually delete the corresponding Conan build and package directories and try to rebuild.

If this still does not work, then try to modify the package recipe adding the [short_paths](http://docs.conan.io/en/latest/reference/conanfile/attributes.html#short-paths) option.
