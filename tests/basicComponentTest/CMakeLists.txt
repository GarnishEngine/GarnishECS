cmake_minimum_required(VERSION 3.22)
project(basicComponentTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(BasicComponentTest main.cc)

target_include_directories(BasicComponentTest PUBLIC ../../include)

target_link_libraries(BasicComponentTest GarnishECS)
