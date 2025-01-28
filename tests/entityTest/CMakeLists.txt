cmake_minimum_required(VERSION 3.22)
project(entityTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(EntityTest main.cc)

target_include_directories(EntityTest PUBLIC ../../include)

target_link_libraries(EntityTest GarnishECS)
