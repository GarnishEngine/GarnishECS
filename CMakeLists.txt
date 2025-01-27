cmake_minimum_required(VERSION 3.22)
project(GarnishECS)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Settings
option(_BUILD_EXAMPLES "Build Examples" ON)

# Add include directory
include_directories("include")

# Add the source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cc")

# Create the library target
add_library(GarnishECS STATIC ${SOURCE_FILES})

# Set the library properties
set_target_properties(GarnishECS PROPERTIES
  PUBLIC_HEADER "include/GarnishECS/garnish_ecs.h"
)

# Install the library and headers
install(TARGETS GarnishECS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/GarnishECS)

# Add the test program
# Building examples:
if (_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif(_BUILD_EXAMPLES)
