# Models/CMakeLists.txt
# Collect all source files in the Models directory
file(GLOB_RECURSE HELPERS_SOURCES "*.cpp")

# Create a library target for the models
add_library(Helpers ${HELPERS_SOURCES})

# Include directories for the Models target
target_include_directories(Helpers PUBLIC ${PROJECT_SOURCE_DIR}/Helpers)
