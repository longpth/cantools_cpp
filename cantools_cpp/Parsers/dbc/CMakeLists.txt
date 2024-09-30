# Parsers/CMakeLists.txt
# Collect all source files in the Parsers directory
file(GLOB_RECURSE DBCPARSERS_SOURCES "*.cpp")

# Create a library target for the parsers
add_library(DBCParsers ${DBCPARSERS_SOURCES})

# Include directories for the Parsers target
target_include_directories(DBCParsers PUBLIC ${PROJECT_SOURCE_DIR}/Parsers/dbc)
