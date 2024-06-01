add_executable(cli cli.cpp)
target_include_directories(cli PRIVATE
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/include>"
)
target_link_libraries(cli PRIVATE CLI11::CLI11)

install(TARGETS cli DESTINATION bin)