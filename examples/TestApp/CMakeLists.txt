cmake_minimum_required(VERSION 3.22)
project(ECSTestApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ECSTestApp test_app.cc)

target_include_directories(ECSTestApp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_libraries(ECSTestApp PRIVATE GarnishECS)
