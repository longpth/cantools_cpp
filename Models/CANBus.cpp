#include "CANBus.hpp"
#include "Logger.hpp"

void CANBus::addNode(const std::shared_ptr<CANNode>& node) {
    _nodes.push_back(node);
}

void CANBus::transmitMessage(const CANMessage& message) {
    Logger::getInstance().log("Transmitting message on CAN Bus: " + _busName, Logger::INFO);
    for (auto& node : _nodes) {
        node->receiveMessage(message);
    }
}

std::string CANBus::getName() const {
    return _busName;
}

std::shared_ptr<CANNode> CANBus::getNodeByName(const std::string& nodeName) const {
    for (const auto& node : _nodes) {
        if (node->getName() == nodeName) {
            return node;
        }
    }
    return nullptr; // Return nullptr if no node with the given name is found
}

void CANBus::addMessage(const std::shared_ptr<CANMessage>& message) {
    _allMessages.push_back(message);
}

std::shared_ptr<CANMessage> CANBus::getMessageById(const uint32_t id) const {
    auto it = std::find_if(_allMessages.begin(), _allMessages.end(),
        [id](const std::shared_ptr<CANMessage>& message) {
            return message->getId() == id;
        });

    if (it != _allMessages.end()) {
        return (*it);
    }
    else {
        return nullptr;
    }
}
