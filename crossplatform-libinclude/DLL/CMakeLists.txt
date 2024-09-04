cmake_minimum_required(VERSION 3.10)
project(DLL)

add_library(DLL SHARED multiply_dll.cpp)
target_include_directories(DLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Set the output name and location for the shared library
set_target_properties(DLL PROPERTIES OUTPUT_NAME "DLL")
