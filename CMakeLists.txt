# Top level CMakeLists.txt file for LEDServer

# set all cmake policies to its NEW behavior
cmake_minimum_required( VERSION  3.3 )

if( EXISTS  "${CMAKE_CURRENT_LIST_DIR}/cmake" )
    list( APPEND  CMAKE_MODULE_PATH  "${CMAKE_CURRENT_LIST_DIR}/cmake" )
endif()


#==============================================================================
# Set the main project name. For Visual Studio, this will create a Solution
# file.

project( LEDServer
         VERSION       0.0.1
         LANGUAGES     C  CXX
)

#==============================================================================
# Standard CMake header config.
# NOTE: Could be a CMake include file.

# Set CMake to support a modern C++ version.
set(CMAKE_CXX_STANDARD 14)
# fail if c++14 is not available
set( CMAKE_CXX_STANDARD_REQUIRED  ON )
# disable compiler-specific extensions
set( CMAKE_CXX_EXTENSIONS  OFF )

# enable using CTest
enable_testing()

option( WITH_TESTS  ""  ON )
option( WITH_DOCS  ""  OFF )
option( WITH_EXAMPLES  ""  OFF )
option( WITH_BENCHMARKS  ""  ON )

# default initialize the output paths
if( NOT  DEFINED  CMAKE_RUNTIME_OUTPUT_DIRECTORY )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/bin" )
endif()
if( NOT  DEFINED  CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib" )
endif()
if( NOT  DEFINED  CMAKE_ARCHIVE_OUTPUT_DIRECTORY )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/lib" )
endif()

# build shared libraries by default
if( NOT  DEFINED  BUILD_SHARED_LIBS )
    set( BUILD_SHARED_LIBS  ON  CACHE  BOOL  ""  FORCE )
endif()

# set the install location
if( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set( CMAKE_INSTALL_PREFIX  ${CMAKE_BINARY_DIR}  CACHE  PATH  ""  FORCE )
endif()

# show targets listed in their folders for IDEs
set_property( GLOBAL  PROPERTY  USE_FOLDERS  ON )


#==============================================================================
# Conan setup
# Assigns to CMake all needed variables for linking with required packages

#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

find_package(Boost REQUIRED COMPONENTS system thread )



# overwrite the build configuration types to just the one conan uses
# (only relevant when using VS/XCode cmake generators)
if( CMAKE_CONFIGURATION_TYPES )
    # only use debug/release build configs
    set( CMAKE_CONFIGURATION_TYPES  "Release;Debug"  CACHE  STRING  ""  FORCE )
endif()

# set verbose warning level
add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/W4>"
    "$<$<CXX_COMPILER_ID:GNU>:-Wall;-Wextra;-Wpedantic>"
    "$<$<CXX_COMPILER_ID:Clang>:-Weverything;-Wno-c++98-compat>"
)

# disable specific warnings
add_compile_options(
    # C4251 (level 1): "class 'A' needs to have dll-interface to be used by clients of class 'B'"
    # C4275 (level 2): "non dll-interface class 'A' used as base for dll-interface class 'B'"
    "$<$<CXX_COMPILER_ID:MSVC>:/wd4251;/wd4275>"
    "$<$<CXX_COMPILER_ID:GNU>:>"
    "$<$<CXX_COMPILER_ID:Clang>:>"
)

# add other misc compiler flags
add_compile_options(
    "$<$<CXX_COMPILER_ID:MSVC>:/MP;/Gm-;/bigobj>"
    "$<$<CXX_COMPILER_ID:GNU>:>"
    "$<$<CXX_COMPILER_ID:Clang>:>"
)

# disable link time optimization for all targets
set( INTERPROCEDURAL_OPTIMIZATION  OFF )

# export all symbols when compiling on windows
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS  ON )

add_definitions(-DGTEST)

#==============================================================================
# Invoke all CMake projects.

# Correctly set RPaths for dylibs in OSX; required for CLion
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
    # override conan disabling rpath
    set( CMAKE_SKIP_RPATH False )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )
    # NEW: when building, add link targets to the rpath
    set( CMAKE_INSTALL_RPATH_USE_LINK_PATH True )
endif()


# add the library target
add_subdirectory(src)

# dev targets
#add_subdirectory(test)

# optional project areas
if( IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/doc" )
    add_subdirectory(doc)
endif()
if( IS_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/examples" )
    add_subdirectory(examples)
endif()

# Debug 
# dump_cmake_vars()
