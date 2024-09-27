cmake_minimum_required(VERSION 3.20)
project(zpp_bits VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(zpp_bits INTERFACE)
target_include_directories(zpp_bits INTERFACE ./)

add_subdirectory(test)
