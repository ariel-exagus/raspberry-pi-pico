# Instruction to compile the basic SDK C/C++ raspberry pi pico project template

This template is intended to compile basics C/C++ project for Raspberry Pi Pico in Windows or Linux. We use CMake, which is multiplatform. Below we put some steps to compile this template. 

## Compile Project
Run this commands to compile the project with CMake

```
$ cd <project_dir>
$ mkdir build
$ cd build
$ cmake -G "MinGW Makefiles" ..
$ make
```

> Note: In Windows Platform we must put the option `-G "MinGW Makefiles"`. Don't forget the "`..`"

This should build the project-template and generate the .elf, .hex and .uf2 binary files. 

## Upload the .uf2 file
After compile successfully, we can upload the program to our Pico. You have to connect the Pico board in bootloader mode (press and hold the BOOTSEL button while plugging a USB cable into the Pico).

Then find the driver letter of the board, you can see a new disc with the name RPI-RP2. Copy the `.uf2` file into the drive mounted. For example, this is the command if your letter drive is F:.

```
$ cp <file_name>.uf2 /f/
```
