

project(terminal-gui
LANGUAGES CXX
VERSION 1.0.0
)

add_executable(terminal-gui main.cpp)
target_include_directories(terminal-gui PRIVATE src)

target_link_libraries(terminal-gui
PRIVATE ftxui::screen
PRIVATE ftxui::dom
PRIVATE ftxui::component # Not needed for this example.
)