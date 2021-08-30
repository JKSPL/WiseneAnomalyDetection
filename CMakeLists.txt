cmake_minimum_required(VERSION 3.4)

project(wisene)
set(CMAKE_CXX_STANDARD 17)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
include_directories(${COMMON_INCLUDES})

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/obstructionPredictor/*.cpp)

add_library(wisene_lib ${SRC_FILES})
add_executable(wisene_stdin ${PROJECT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(wisene_stdin wisene_lib)

add_subdirectory(./googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/*.cpp)
add_executable(runUnitTests ${TEST_SRC_FILES})
target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests wisene_lib)

add_test(UnitTests runUnitTests)