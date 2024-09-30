# Models/CMakeLists.txt
# Collect all source files in the Models directory
file(GLOB_RECURSE MODEL_SOURCES "*.cpp")

# Create a library target for the models
add_library(CANModels ${MODEL_SOURCES})

# Include directories for the Models target
target_include_directories(CANModels PUBLIC ${PROJECT_SOURCE_DIR}/Models)
