# Set up a local cache directory instead of relying on env
find_package(Git)
if(NOT Git_FOUND)
  message(FATAL_ERROR "Expecting git on system!")
endif()
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --show-toplevel
    OUTPUT_VARIABLE GIT_ROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND_ERROR_IS_FATAL ANY
)
cmake_path(SET GIT_ROOT "${GIT_ROOT}")
cmake_path(
    APPEND CPM_LOCAL_CACHE
    "${GIT_ROOT}" "cpm-cache"
)

if(EXISTS "$ENV{CPM_SOURCE_CACHE}")
  message(STATUS "Using env CPM cache ${CPM_SOURCE_CACHE}")
elseif(NOT IS_DIRECTORY ${CPM_LOCAL_CACHE})
  file(MAKE_DIRECTORY ${CPM_LOCAL_CACHE})
  set(CPM_SOURCE_CACHE ${CPM_LOCAL_CACHE})
else()
  set(CPM_SOURCE_CACHE ${CPM_LOCAL_CACHE})
endif()
message(STATUS "CPM cache set to ${CPM_SOURCE_CACHE}")

set(CMAKE_FIND_ROOT_PATH ${CPM_SOURCE_CACHE})
set(CPM_USE_LOCAL_PACKAGES TRUE)
# TODO: unclear why this throws errors
#set(CPM_LOCAL_PACKAGES_ONLY TRUE)