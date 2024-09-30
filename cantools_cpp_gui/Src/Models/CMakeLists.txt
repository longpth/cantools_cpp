# Models/CMakeLists.txt
# Collect all source files in the Models directory
file(GLOB_RECURSE MODELS_SOURCES "*.cpp")

# Create a library target for the models
add_library(GUIModels ${MODELS_SOURCES})

# Include directories for the Models target
target_include_directories(GUIModels PUBLIC ${PROJECT_SOURCE_DIR}/Models)
