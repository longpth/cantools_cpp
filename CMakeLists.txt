# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the top-level project
project(cantools_cpp_solution VERSION 1.0)

# Specify the C++ standard (if needed for the top-level)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectories for the two projects
add_subdirectory(cantools_cpp)
add_subdirectory(cantools_cpp_gui)
