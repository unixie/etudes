cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(
  dlopen-user
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
  NAME ftxui
  GIT_TAG v5.0.0
  GITHUB_REPOSITORY arthursonzogni/ftxui
  EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
  NAME CLI11
  GIT_TAG v2.4.2
  GITHUB_REPOSITORY CLIUtils/CLI11
)

# === Project tree ============================================================
#add_subdirectory(lib)
add_subdirectory(apps)


# === Install =================================================================
