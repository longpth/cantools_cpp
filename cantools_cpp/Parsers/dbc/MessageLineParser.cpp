#include "MessageLineParser.hpp"
#include "CANMessage.hpp"
#include "CANBus.hpp"

namespace cantools_cpp
{

    // Static members initialization
    const std::string MessageLineParser::MessageLineStarter = "BO_ ";
    const std::regex MessageLineParser::MessageRegex(
        R"(BO_ (\d+)\s+([a-zA-Z_]\w*)\s*:\s*(\d+)\s+([a-zA-Z_]\w*))");

    bool MessageLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) {
        std::string _trimmed = line; // Copy line to trim it
        _trimmed.erase(0, _trimmed.find_first_not_of(" \t\n\r\f\v")); // Left trim

        if (_trimmed.substr(0, MessageLineStarter.length()) != MessageLineStarter)
            return false;

        std::smatch _match;
        if (std::regex_search(_trimmed, _match, MessageRegex) && _match.size() > 4) {
            std::shared_ptr<CANMessage> msg = std::make_shared<CANMessage>(static_cast<unsigned int>(std::stoul(_match.str(1))));
            msg->setName(_match.str(2));  // Use setter for the name
            msg->setLength(static_cast<unsigned short>(std::stoi(_match.str(3)))); // Use setter for DLC, parsing the size
            msg->setTransmitter(_match.str(4)); // Use setter for the transmitter

            auto canNode = busMan->getBus(busName)->getNodeByName(msg->getTransmitter());

            if (canNode)
            {
                canNode->addMessage(msg);
            }

            return true;
        }

        // Implement failure notification logic here if needed
        return false;
    }
}