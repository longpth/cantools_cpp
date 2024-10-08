﻿# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(cantools_cpp VERSION 1.0)

# Set the output directory for build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/Models)
include_directories(${PROJECT_SOURCE_DIR}/Parsers)
include_directories(${PROJECT_SOURCE_DIR}/Parsers/dbc)
include_directories(${PROJECT_SOURCE_DIR}/Helpers)

# Add subdirectories
add_subdirectory(Helpers)
add_subdirectory(Models)
add_subdirectory(Parsers)
add_subdirectory(Parsers/dbc)

# Create the static library
add_library(cantools_cpp STATIC main.cpp)

target_link_libraries(cantools_cpp PUBLIC CANModels CANParsers DBCParsers Helpers)
