# Connected Vision

## Build on Linux with GCC:
1. `sudo apt-get install git`
2. `sudo apt-get install build-essential`
3. `sudo apt-get install cmake` (version >= 3.0.0)
4. `sudo apt-get install python-pip`
possibly `sudo pip install --upgrade pip`
5. `sudo pip install conan`
`sudo pip install setuptools` (only necessary if a corresponding Conan error occurs)
6. `conan search`
7. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
8. build the Connected Vision Conan package either explicitly by calling
`conan install ConnectedVision/0.0.1@covi/stable -b outdated`
or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build on Windows with Visual Studio:
1. install `git`
2. install `cmake` (version >= 3.0.0)
3. install `python` including `pip`
4. `pip install conan` (from console with administrator rights)
5. `conan search`
6. `conan remote add covi https://api.bintray.com/conan/covi/ConnectedVision`
7. build the Connected Vision Conan package either explicitly by calling
`conan install ConnectedVision/0.0.1@covi/stable -b outdated`
or implicitly by referencing it from within another project as done in the [Connected Vision Demo Server](https://github.com/ConnectedVision/connectedvision-apps/tree/master/DemoServer/build/cmake)

## Build tested with...
| OS                  | OS architecture | compiler                | compiler version   | build architecture |
|:-------------------:|:---------------:|:-----------------------:|:------------------:|:------------------:|
| Windows 7           | 64 bit          | MSVC                    | Visual Studio 2010 | 32 & 64 bit        |
| Windows 10          | 64 bit          | MSVC                    | Visual Studio 2015 | 64 bit             |
| Ubuntu 12.04 LTS    | 64 bit          | GCC                     | 4.6.3              | 64 bit             |
| Ubuntu 12.04 LTS    | 64 bit          | arm-linux-gnueabihf-gcc | 4.6.3              | armv7hf            |
| Ubuntu server 14.04 | 64 bit          | GCC                     | 4.8.4              | 64 bit             |
| Linux Mint 17.3     | 32 bit          | GCC                     | 4.8.4              | 32 bit             |
| Linux Mint 17.3     | 64 bit          | GCC                     | 4.8.4              | 64 bit             |
| Linux Mint 18.1     | 64 bit          | GCC                     | 5.4.0              | 64 bit             |
| Linux Mint 18.2     | 64 bit          | GCC                     | 5.4.0              | 64 bit             |
