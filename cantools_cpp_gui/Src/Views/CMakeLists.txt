# Models/CMakeLists.txt
# Collect all source files in the Models directory
file(GLOB_RECURSE VIEWS_SOURCES "*.cpp")

# Create a library target for the models
add_library(GUIViews ${VIEWS_SOURCES})

# Include directories for the Models target
target_include_directories(GUIViews PUBLIC ${PROJECT_SOURCE_DIR}/Views)
