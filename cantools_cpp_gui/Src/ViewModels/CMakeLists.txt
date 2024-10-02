# Models/CMakeLists.txt
# Collect all source files in the Models directory
file(GLOB_RECURSE CONTROLLERS_SOURCES "*.cpp")

# Create a library target for the models
add_library(GUIControllers ${CONTROLLERS_SOURCES})

# Include directories for the Models target
target_include_directories(GUIControllers PUBLIC ${PROJECT_SOURCE_DIR}/ViewModels)
