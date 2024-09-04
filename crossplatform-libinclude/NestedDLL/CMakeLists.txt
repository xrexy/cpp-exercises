cmake_minimum_required(VERSION 3.10)
project(NestedDLL)

add_library(NestedDLL SHARED circle.cpp)
target_include_directories(NestedDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(NestedDLL PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../DLL)

# Link against the dll library
target_link_libraries(NestedDLL PRIVATE DLL)

# Set the output name and location for the shared library
set_target_properties(NestedDLL PROPERTIES OUTPUT_NAME "NestedDLL")
