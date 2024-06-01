# Include guard
# https://github.com/TheLartians/ModernCppStarter/blob/master/CMakeLists.txt
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()