# Instruction for install SDK C&C++ toolchains of Raspberry pi PICO on Windows

Source: https://shawnhymel.com/2096/how-to-set-up-raspberry-pi-pico-c-c-toolchain-on-windows-with-vs-code/

## 1. Create Directory Setup

We must create a directory VSARM with the following Subdirectories

```
D:\VSARM\armcc
D:\VSARM\lib
D:\VSARM\mingw
D:\VSARM\sdk
```

## 2- Download the ARM GCC Toolchain
Use this link to download the ARM GCC Toolchain:
https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads

Then install on: 
```
D:\VSARM\armcc\10 2020-q4-major
```

On the final windows, you must check the option "Add path to environment variable." So you can run arm-none-eabi-gcc in the prompt command windows

## 3- Install MinGW64:
Download the MinGW64
http://mingw-w64.org/doku.php/download/mingw-builds

Install the 32-bit version on the directory `D:\VSARM\mingw`

Then open a windows command prompt and execute the next command
```
echo mingw32-make %* > C:\VSARM\mingw\mingw32\bin\make.bat
```

## 4- Install CMake Tool
Download the CMake tool: https://cmake.org/download/ 
(Download version 3.19.8, the 3.20 has a bug)

Important
- On Install Options, select Add CMake to the system PATH for all users.

## 5- Install Python 3.9
Download and install Python 3.9: https://www.python.org/downloads/

On the first screen of installer, make sure that "Install launcher for all users (recommended)" is checked and check "Add Python 3.9 to PATH"

At the end of the installation process, select the option to disable the MAX_PATH length limit.

> Important! If you were not asked to disable the MAX_PATH length limit, you will want to make sure that long paths are enabled. The Pico SDK (and many other SDKs) often have long, nested folders, resulting in pathnames that exceed the original Windows limit (260 characters).

To enable long paths, search for regedit in the Windows search bar and run the Registry Editor program. Navigate to Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\FileSystem and add an entry (if one is not already there) for LongPathsEnabled. Change Value data to 1 and Base to Hexadecimal. 

## 6- Install GIT

## 7- Download and intall the Pico SDK

Download the Pico SDK from Git Repositorie

  a. Create a new folder named "pico" in `D:\VSARM\sdk`
  
  b. Go to pico folder and open the Git Bash. Then we must execute the folowing commands
  
  ```
	$ cd /c/VSARM/sdk/pico 
	$ git clone -b master https://github.com/raspberrypi/pico-sdk.git 
	$ cd pico-sdk 
	$ git submodule update --init 
	$ cd .. 
	$ git clone -b master https://github.com/raspberrypi/pico-examples.git
  ```

## 8- Update the Enviroment Variables
We need to update the enviroment variables for Mingw and SDK. (The other tools update the environment variables automaticaly)

We must Add in "Path" for User variables the route to mingw32 "D:\VSARM\mingw\mingw32\bin" in my case.
Then, in User variables, click en "New" and add the following User variable:
- Variable Name: PICO_SDK_PATH
- Variable value: D:\VSARM\sdk\pico\pico-sdk

Under system variables, select Path and check if the followings Path are present
-C:\Program Files\CMake\bin
-C:\Program Files\Git\cmd

Then, click OK in all windows to update the envirenment variables. At this moment you can open a command prompt and check if you can execute 'gcc', 'make' and 'echo %PICO_SDK_PATH%

## 9- Build Exmaple
We recommend creating an alias for mingw32-make in git bash. Doing this with the following commands

```
$ echo "alias make=mingw32-make.exe" >> ~/.bashrc
$ source ~/.bashrc
```

Build the blink example with the following commands
```
$ cd /c/VSARM/sdk/pico/pico-examples/
$ mkdir build
$ cd build
$ cmake -G "MinGW Makefiles" ..
$ cd blink
$ make
```
> Important: In windows Platform, any time you call CMake, you must add '-G "MinGW Makefiles" option to specify the build system.

# Update SDK Raspberry pi pico

## 1- Update SDK Pico

To update de the SDK Pico, you must to go to the SDK pico directory

```
$ cd <sdk-pico-directory>/pico-sdk
```

Use `git` to download the last version of the SDK pico from the oficial repository of Raspberry pi in GitHub

```
git pull origin master
```

This bring the updating and recents changing in the SDK

## 2- Update Submodules

Some of components of SDK are submodules in git. Make sure that they are updating.

```
git submodule update --init --recursive
```

To check the actual version, you can see the log register of repository

```
git log -1
```


