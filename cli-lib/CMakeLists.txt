cmake_minimum_required(VERSION 3.12)

# Before use this CMake, you must define the enviroment variable "PICO_SDK_PATH"
# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME)
project(cli-lib-v110 C CXX ASM)

# specify the C standard
set(CMAKE_C_STANDARD 11)
# Opcional: Requerir el estándar explícitamente sin permitir extensiones del compilador.
set(CMAKE_C_STANDARD_REQUIRED true)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add all the sources files in src
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

# Add main.cpp file
set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/main.c)

# Add the executables
add_executable(${PROJECT_NAME} ${SOURCES})

#In windows, use the next command to generate de MakeFile: cmake .. -G "MinGW Makefiles"

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})

# Link to pico_stdlib (gpio, time, tec. functions)
target_link_libraries(${PROJECT_NAME}
    pico_stdlib
)

# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)