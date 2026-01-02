cmake_minimum_required(VERSION 3.22)
project(sceneComponentTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(sceneComponentTest main.cc)

target_include_directories(sceneComponentTest PUBLIC ../../include)

target_link_libraries(sceneComponentTest 
    PRIVATE 
    GarnishECS
    gtest_main
)
