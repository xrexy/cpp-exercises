cmake_minimum_required(VERSION 3.10)
project(Static)

add_library(Static STATIC multiply_static.cpp)
target_include_directories(Static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the output name and location for the Static library
set_target_properties(Static PROPERTIES OUTPUT_NAME "static")
