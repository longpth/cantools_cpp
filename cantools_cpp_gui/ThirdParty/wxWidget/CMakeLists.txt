# check if wxWidgets is already installed in the system - using CMake's built in script FindwxWidgets
find_package(wxWidgets QUIET)

if(wxWidgets_FOUND)
    message(STATUS "Found preinstalled wxWidgets libraries at ${wxWidgets_LIBRARIES}")
    add_library(wxWidgets_external INTERFACE)
else()
    message(STATUS "Preinstalled wxWidgets not found.")
endif()