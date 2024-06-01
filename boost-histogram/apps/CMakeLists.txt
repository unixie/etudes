add_executable(cli cli.cpp)
target_include_directories(cli PRIVATE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)
target_link_libraries(cli PRIVATE CLI11::CLI11 fmt::fmt histogram Boost::histogram)