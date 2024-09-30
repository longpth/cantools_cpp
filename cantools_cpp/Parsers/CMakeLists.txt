# Parsers/CMakeLists.txt
# Collect all source files in the Parsers directory
file(GLOB_RECURSE PARSER_SOURCES "*.cpp")

# Create a library target for the parsers
add_library(CANParsers ${PARSER_SOURCES})

# Include directories for the Parsers target
target_include_directories(CANParsers PUBLIC ${PROJECT_SOURCE_DIR}/Parsers)

# Link the CANModels library to CANParsers
target_link_libraries(CANParsers PUBLIC CANModels DBCParsers)
