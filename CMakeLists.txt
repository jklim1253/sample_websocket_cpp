cmake_minimum_required(VERSION 3.0)

if(CMAKE_BUILD_TYPE MATCHES "^[Dd][Ee][Bb][Uu][Gg]$" OR NOT DEFINED CMAKE_BUILD_TYPE)
  set(VCPKG_VERBOSE ON)
endif()

if(NOT DEFINED ENV{VCPKG_ROOT})
  message(FATAL_ERROR "this project use `vcpkg` package manager.")
else()
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
  message(STATUS "VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")

  if(WIN32)
    set(VCPKG_INCLUDE_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/include" CACHE PATH "")
    set(VCPKG_LIBRARY_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/lib" CACHE PATH "")
    set(VCPKG_LIBRARY_RELEASE_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/lib" CACHE PATH "")
    set(VCPKG_LIBRARY_DEBUG_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/debug/lib" CACHE PATH "")
    set(VCPKG_BINARY_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/bin" CACHE PATH "")
    set(VCPKG_BINARY_RELEASE_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/bin" CACHE PATH "")
    set(VCPKG_BINARY_DEBUG_DIR "$ENV{VCPKG_ROOT}/installed/x64-windows/debug/bin" CACHE PATH "")
  else()
    # TODO: set directories for linux
    message(FATAR_ERROR "erase this message and set directories for linux")
  endif()
endif()

project(sample)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(AFTER SYSTEM ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)