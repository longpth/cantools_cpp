# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(cantools_cpp_gui VERSION 1.0)

# Set the output directory for build artifacts
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/Src)
include_directories(${PROJECT_SOURCE_DIR}/Src/Models)
include_directories(${PROJECT_SOURCE_DIR}/Src/ViewModels)
include_directories(${PROJECT_SOURCE_DIR}/Src/Views)
include_directories(${PROJECT_SOURCE_DIR}/ThirdParty)

# Add subdirectories
add_subdirectory(Src)
add_subdirectory(ThirdParty)
