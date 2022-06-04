
cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(SCRIPTS_PATH "${CMAKE_SOURCE_DIR}/tools/scripts")

include(${CMAKE_MODULE_PATH}/arm-gcc-toolchain.cmake)

set(USE_PYTHON_VERSION "" CACHE STRING "Optional user-selected Python version")
if(USE_PYTHON_VERSION)
  find_package(Python ${USE_PYTHON_VERSION} EXACT COMPONENTS Interpreter REQUIRED)
else()
  find_package(Python COMPONENTS Interpreter REQUIRED)
endif()

if(NOT Python_FOUND )
message(FATAL_ERROR "Python3 not found. You need Python 3.7 to build this program")
endif()

set(PYTHON  "${Python_EXECUTABLE}")

project(upg200 LANGUAGES C ASM DESCRIPTION "Universal Pulse Generator")

add_compile_options(
    -mcpu=cortex-m3
    -mthumb
    -O0  
    -gdwarf-3 
    -ggdb
    -ffunction-sections
    -fdata-sections
    -fno-omit-frame-pointer
    -Wall
    -Wfatal-errors
    -nostartfiles
    -specs=nosys.specs
    -std=gnu11
)

add_link_options(    
  -mcpu=cortex-m3
)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
  add_compile_options(-O0)
  message("-- Warning: This is a DEBUG build. Not suitable for release purposes ")
  message("-- Enabling debug symbols ")
else()
  message("-- Info: This is a release build")
  add_compile_options(-O3)
  add_compile_definitions(NDEBUG)
endif()

add_compile_definitions(STM32F107xC)

include(${CMAKE_MODULE_PATH}/gitversion.cmake)
get_repository_version()
add_definitions(-DGIT_VERSION=\"${GIT_VERSION}\")
add_definitions(-DGIT_VERSION_MAJOR=${GIT_VERSION_MAJOR})
add_definitions(-DGIT_VERSION_MINOR=${GIT_VERSION_MINOR})
add_definitions(-DGIT_VERSION_PATCH_LEVEL=${GIT_VERSION_PATCH_LEVEL})
add_definitions(-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH})
add_definitions(-DGIT_COMMIT_HASH_HEX=0x${GIT_COMMIT_HASH})

add_subdirectory(src/platform)
add_subdirectory(src/application)

add_custom_target(flash COMMAND ${Python_EXECUTABLE} 
    ${SCRIPTS_PATH}/jlink_flasher.py
    -d "STM32F107RC"
    -iface "SWD"
    ${CMAKE_SOURCE_DIR}/dist/upg200_${GIT_VERSION}.hex
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/dist
    DEPENDS upg200_${GIT_VERSION}.hex
)
