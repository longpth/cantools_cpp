#include <string>
#include <algorithm>
#include "CANNode.hpp"
#include "CANBusManager.hpp"
#include "CANBus.hpp"


CANNode::CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager)
    : _nodeName(name) {
    _connectedBus = busManager.getBus(busName);
    if (_connectedBus) {
        _connectedBus->addNode(std::make_shared<CANNode>(*this));
        std::cout << "Node " << _nodeName << " connected to CAN Bus " << busName << std::endl;
    }
}

void CANNode::receiveMessage(const CANMessage& message) {
    std::cout << "Node " << _nodeName << " received message ID: " << message.getId() << " from Bus " << _connectedBus->getName() << std::endl;
}

void CANNode::sendMessage(const CANMessage& message) {
    if (_connectedBus) {
        _connectedBus->transmitMessage(message);
    }
    else {
        std::cerr << "Node " << _nodeName << " is not connected to any CAN Bus." << std::endl;
    }
}

void CANNode::addMessage(const std::shared_ptr<CANMessage>& msg) {
    // Check if a message with the same name already exists in the _txMessages
    bool exists = std::any_of(_txMessages.begin(), _txMessages.end(),
        [&msg](const std::shared_ptr<CANMessage>& existingMsg) {
            return existingMsg->getName() == msg->getName();
        });

    if (!exists) {
        // If no message with the same name exists, add it to the local storage and the connected bus
        _txMessages.push_back(msg);
        _connectedBus->addMessage(msg);
    }
}
