cmake_minimum_required(VERSION 2.8.6)
project(EuropeanOption)

enable_testing()

#
# Set configuration
#

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
    set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()

if(CMAKE_GENERATOR MATCHES "Makefiles|Ninja" AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

option(COVERAGE "Build with coverage support" OFF)

#
# Setup output directories
#

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${cfg}" cfg)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_PDB_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
endforeach()

#
# Add compiler options: enable C++11, all warnings, fail on warnings
#

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
#    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "ICC" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
    if(COVERAGE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

#
# Add Google Test
#

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/gtest")
set(LIBRARY_DEPS "gtest")

#
#
#
# Include all modules
#

file(GLOB SUBDIRS "${CMAKE_CURRENT_SOURCE_DIR}/modules/*")

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()
