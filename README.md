# Firmware for Teensy 3.6 Based EIT Device


## TODO 


## Requirements (Before you start)

### Linux (Debian)


1. Install ARM GNU Tool Chain
```
wget https://developer.arm.com/-/media/Files/downloads/gnu/11.2-2022.02/binrel/gcc-arm-11.2-2022.02-aarch64-arm-none-eabi.tar.xz
```
2. TODO: Finish this


```
sudo apt-get update -y
sudo apt-get install -y gcc make build-essential openocd gdb-multiarch cmake
```

### Windows 10

1. Install the [GNU Arm Embedded Toolchain for Windows](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads).  BARE METAL TARGET 32 BIT, current release (NOT BETA) [11.2.2-2022](wget https://developer.arm.com/-/media/Files/downloads/gnu/11.2-2022.02/binrel/gcc-arm-11.2-2022.02-mingw-w64-i686-arm-none-eabi.exe)
2. Install [MinGW for Windows](http://sourceforge.net/projects/mingw/files/Installer/)  
3. Install [CMake for Windows](https://cmake.org/download/)
4. Edit the env.cmd file to specify the paths to the tools you just installed.


## Compiling  
  
1. Run generate_makefiles (.bat for windows, .sh for linux), this is only needed once
2. Run make_debug (.bat for windows, .sh for linux)