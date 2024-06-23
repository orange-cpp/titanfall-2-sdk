cmake_minimum_required(VERSION 3.28)

project(cv-sdk)

add_library(sig INTERFACE)
target_include_directories(sig INTERFACE include)
target_link_directories(sig INTERFACE lib)