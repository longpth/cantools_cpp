cmake_minimum_required(VERSION 3.10)
project(MyWxApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

if(wxWidgets_FOUND)
    message(STATUS "Found preinstalled wxWidgets libraries at ${wxWidgets_LIBRARIES}")
else()
    message(FATAL_ERROR "Preinstalled wxWidgets not found.")
endif()

# Include wxWidgets use file
include(${wxWidgets_USE_FILE})

# Add the executable with the WIN32 keyword
add_executable(MyWxApp WIN32 main.cpp "Views/GUIView.cpp" "Views/TabDatabaseView.cpp" "Models/BusManager.cpp" "ViewModels/CANViewModel.cpp" "Models/Bus.cpp" "Models/Message.cpp" "Models/Signal.cpp")

# Link wxWidgets libraries
target_link_libraries(MyWxApp ${wxWidgets_LIBRARIES} cantools_cpp)

# Set the subsystem to Windows if on WIN32
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()