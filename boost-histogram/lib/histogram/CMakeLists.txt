add_library(histogram_obj OBJECT histogram.cpp)

target_include_directories(histogram_obj PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(histogram_obj PROPERTIES
  PUBLIC_HEADER lib/histogram/include/histogram/histogram.hpp
  POSITION_INDEPENDENT_CODE ON
)
target_link_libraries(histogram_obj PRIVATE fmt::fmt Boost::histogram)


add_library(histogram STATIC)
target_link_libraries(histogram PRIVATE histogram_obj)