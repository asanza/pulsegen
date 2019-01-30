cmake_minimum_required(VERSION 3.6)

# Enable export of compilation database for further analysis
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the path to custom modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# include compiler definition from:
# include(tools/cmake/arm-iar-toolchain.cmake)
include(${CMAKE_MODULE_PATH}/arm-gcc-toolchain.cmake)

project(NUCLEO_103 C ASM)

# These are the compile flags when using gnu compiler.
add_compile_options(
    -mcpu=cortex-m3 
    -fomit-frame-pointer
    -O0
    -gdwarf-3 
    -ggdb 
    -mthumb
    -ffunction-sections
    -fno-strict-aliasing
    -fdata-sections
    -fexpensive-optimizations
    -Wall
    -Wfatal-errors
    -funsigned-char
    -ffreestanding
    -fmerge-all-constants
)

set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m3")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,-flto")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -nostdlib") 
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")

# Set the current git branch name into the GIT_BRANCH variable
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git describe --abbrev=6 --dirty --always
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the tag name as version indicator.
execute_process(
  COMMAND git describe --always --dirty --tags
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND bash "-c" "git describe --tags | cut -d. -f1"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION_MAJOR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND bash "-c" "git describe --tags | cut -d. -f2"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION_MINOR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND bash "-c" "git describe --tags | cut -d. -f3 | cut -d- -f1"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION_PATCH_LEVEL
  OUTPUT_STRIP_TRAILING_WHITESPACE
)


# add custom definitions if debug build active
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  # some debug info
  add_compile_options(-ggdb)
  message("-- Warning: This is a debug build. Not suitable for production purposes")
else()
  # disable assert in release mode
  add_definitions(-DNDEBUG)
  # no debug info
  add_compile_options(-g0)
  message("-- Info: This is a release build.")
endif()

add_definitions(-DGIT_VERSION=\"${GIT_VERSION}\")
add_definitions(-DGIT_VERSION_MAJOR=${GIT_VERSION_MAJOR})
add_definitions(-DGIT_VERSION_MINOR=${GIT_VERSION_MINOR})
add_definitions(-DGIT_VERSION_PATCH_LEVEL=${GIT_VERSION_PATCH_LEVEL})

ADD_SUBDIRECTORY(src/arch)
# ADD_SUBDIRECTORY(src/bsp)
# ADD_SUBDIRECTORY(src/lib)
ADD_SUBDIRECTORY(src/os)
ADD_SUBDIRECTORY(src/sys)
ADD_SUBDIRECTORY(src/app)

find_program(openocd "openocd")

add_custom_target(flash DEPENDS app 
  COMMAND ${openocd} -f board/st_nucleo_f103rb.cfg 
      -c "program app reset"
      -c "exit")
#