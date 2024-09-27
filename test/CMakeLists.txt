cmake_minimum_required(VERSION 3.20)
project(zpp_bits_test VERSION 1.0.0)
include(gtest.cmake)

add_executable(tests)

# add target_sources, all .cpp files in src/ directory
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
target_sources(tests PRIVATE ${TEST_SOURCES})

# add include directories
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add link libraries
target_link_libraries(tests PRIVATE zpp_bits gtest_main)
