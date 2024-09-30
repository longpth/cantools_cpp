// ExtraMessageLineParser.cpp
#include <iostream>
#include <sstream>
#include "ExtraMessageLineParser.hpp"
#include "CANBus.hpp"

namespace cantools_cpp
{

    // Static members initialization
    const std::string ExtraMessageLineParser::ExtraMessageTransmitterLineStarter = "BO_TX_BU_ ";
    const std::regex ExtraMessageLineParser::ExtraTransmitterRegex(
        R"(BO_TX_BU_ (\d+)\s*:\s*((\s*(?:[a-zA-Z_][\w]*)\s*(?:,)?)+);)");

    std::vector<std::string> splitTransmitters(const std::string& transmitters) {
        std::vector<std::string> result;
        std::stringstream ss(transmitters);
        std::string item;

        while (std::getline(ss, item, ',')) {
            // Trim spaces from the beginning and end of the item
            auto start = item.find_first_not_of(" \t\n\r\f\v");
            auto end = item.find_last_not_of(" \t\n\r\f\v");
            if (start != std::string::npos) {
                item = item.substr(start, (end - start + 1));
            }
            result.push_back(item);
        }

        return result;
    }

    bool ExtraMessageLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) {
        std::string _trimmed = line;
        _trimmed.erase(0, _trimmed.find_first_not_of(" \t\n\r\f\v")); // Left trim

        if (_trimmed.substr(0, ExtraMessageTransmitterLineStarter.length()) != ExtraMessageTransmitterLineStarter)
            return false;

        std::smatch _match;
        if (std::regex_search(_trimmed, _match, ExtraTransmitterRegex) && _match.size() > 2) {
            unsigned int messageId = std::stoul(_match.str(1));
            std::string transmitters = _match.str(2);

            // Assuming processTransmitters is a method in CANBusManager to handle the list of transmitters for a message
            busMan->getBus(busName)->getMessageById(messageId)->setAdditionalTransmitters(splitTransmitters(transmitters));
            return true;
        }

        // If regex match fails or is incorrect, handle accordingly
        return false;
    }
}