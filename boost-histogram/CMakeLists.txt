cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  learn-histogram
  VERSION 1.0
  LANGUAGES CXX
  )

# CXX global configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# === CMake includes ==========================================================
cmake_path(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}" ".." "cmake")
cmake_path(NORMAL_PATH CMAKE_MODULE_PATH)
# Note: since updating module path, includes should NOT have .cmake on files
# Include debugging utilities
include(CMakePrintHelpers)
# Basic project checks
include(guard)
# Setup CPM
include(cpm-cache)
include(CPM)


# === Dependencies ============================================================
CPMAddPackage(
  NAME CLI11
  GIT_TAG v2.4.2
  GITHUB_REPOSITORY CLIUtils/CLI11
)

CPMAddPackage(
  NAME fmt
  GIT_TAG 9.1.0
  GITHUB_REPOSITORY fmtlib/fmt
)

set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_DEBUG                 OFF) # enable to debug underlying FindBoost
# Explicitly list dependencies, even header-only
set(BOOST_INCLUDE_LIBRARIES     histogram)
CPMAddPackage(
  NAME Boost
  VERSION 1.84.0
  URL https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.xz
  URL_HASH SHA256=2e64e5d79a738d0fa6fb546c6e5c2bd28f88d268a2a080546f74e5ff98f29d0e
  OPTIONS "BOOST_ENABLE_CMAKE ON"
  EXCLUDE_FROM_ALL YES
)


# === Project tree ============================================================
add_subdirectory(lib)
add_subdirectory(apps)
