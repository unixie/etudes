set(ME cli)

add_executable(${ME} cli.cpp)

target_include_directories(${ME}
PRIVATE
    ../../dlopen/install/include
)

target_link_libraries(${ME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE CLI11::CLI11
)