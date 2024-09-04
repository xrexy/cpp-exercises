cmake_minimum_required(VERSION 3.10)
project(Console)

add_executable(Console main.cpp)

# Include headers from dll, nested_dll, and static
target_include_directories(Console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../DLL)
target_include_directories(Console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../NestedDLL)
target_include_directories(Console PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../Static)

# Link against dll, nested_dll, and static
target_link_libraries(Console PRIVATE DLL NestedDLL Static)
