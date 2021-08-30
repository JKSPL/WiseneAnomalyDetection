cmake_minimum_required(VERSION 3.21)
project(wisene)

set(CMAKE_CXX_STANDARD 17)
include_directories("${CMAKE_SOURCE_DIR}")
add_executable(wisene main.cpp obstructionPredictor/obstructionPredictor.cpp obstructionPredictor/obstructionPredictor.hpp obstructionPredictor/ad_utils.h obstructionPredictor/ad_utils.cpp)