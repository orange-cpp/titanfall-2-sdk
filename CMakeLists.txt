cmake_minimum_required(VERSION 3.28)

project(titanfall-2-sdk)

set(CMAKE_CXX_STANDARD 26)
add_library(titanfall2-sdk STATIC source/Player.cpp)


target_include_directories(titanfall2-sdk PUBLIC include)
target_compile_options(titanfall2-sdk PRIVATE /W4 /WX)

add_subdirectory(source)
add_subdirectory(extlibs)
add_subdirectory(include/titanfall_2)

target_link_libraries(titanfall2-sdk PRIVATE minhook sig d3d11 uml)
target_link_libraries(titanfall2-sdk PUBLIC uml)
target_compile_definitions(titanfall2-sdk PRIVATE WIN32_LEAN_AND_MEAN)