cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  dlopen
  VERSION 1.0
  LANGUAGES CXX
  )

# CXX global configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Keep here for educational purpose since using atexit handler
# Below is in case the standard 32 slots are somehow all in use
#add_compile_options(
#  -fno-register-global-dtors-with-atexit
#)


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


# === Project tree ============================================================
add_subdirectory(lib)
add_subdirectory(apps)


# === Install =================================================================
set(CMAKE_INSTALL_PREFIX
  "${PROJECT_SOURCE_DIR}/install"
  CACHE PATH "default install path" FORCE
)
