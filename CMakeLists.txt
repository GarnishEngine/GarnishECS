cmake_minimum_required(VERSION 3.22)
project(GarnishECS)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directory
include_directories("include")

# Add the source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cc")

# Create the library target
add_library(GarnishECS STATIC ${SOURCE_FILES})

# Set the library properties
set_target_properties(GarnishECS PROPERTIES
  PUBLIC_HEADER "include/GarnishECS/ECS.h"
)

# Install the library and headers
install(TARGETS GarnishECS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/GarnishECS)

# Add the test program
add_executable(GarnishECSTest "tests/main.cc")
target_link_libraries(GarnishECSTest GarnishECS)
