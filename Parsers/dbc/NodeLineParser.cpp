// NodeLineParser.cpp
#include <iostream>
#include <sstream>
#include "NodeLineParser.hpp"
#include "CANBus.hpp"

const std::string NodeLineParser::NameGroup = "Name";

// Constructor
NodeLineParser::NodeLineParser()
    : _regex(R"(BU_:\s*((?:\s+[a-zA-Z_][\w]*\s*)+))") {}

bool NodeLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busManager, std::string busName) {
    // Check if the line starts with "BU_:"
    if (line.find(NodeLineStarter) != 0)
        return false;

    // If the line is just "BU_:", it's considered valid but contains no nodes
    if (line == NodeLineStarter)
        return true;

    // Attempt to match the regex
    std::smatch match;
    if (std::regex_match(line, match, _regex)) {
        // Extract the matched node names
        std::istringstream nodeStream(match.str(1));
        std::string nodeName;

        while (nodeStream >> nodeName) {
            // Add each node name to the CANBusManager
            std::shared_ptr<CANNode> node = std::make_shared<CANNode>(nodeName, busName, *busManager.get());
        }
    }
    else {
        // Instead of using an observer, you can handle errors directly here
        std::cerr << "Node syntax error encountered in line: " << line << std::endl;
    }

    return true;
}
