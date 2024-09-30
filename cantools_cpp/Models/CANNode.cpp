#include <string>
#include <algorithm>
#include "CANNode.hpp"
#include "CANBusManager.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    CANNode::CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager)
        : _nodeName(name) {
        _connectedBus = busManager.getBus(busName);
        if (_connectedBus) {
            _connectedBus->addNode(std::make_shared<CANNode>(*this));
            Logger::getInstance().log("Node " + _nodeName + " connected to CAN Bus " + busName, Logger::INFO);
        }
    }

    void CANNode::receiveMessage(const CANMessage& message) {
        Logger::getInstance().log("Node " + _nodeName + " received message ID: " + std::to_string(message.getId()) + " from Bus " + _connectedBus->getName(), Logger::INFO);
    }

    void CANNode::sendMessage(const CANMessage& message) {
        if (_connectedBus) {
            _connectedBus->transmitMessage(message);
        }
        else {
            Logger::getInstance().log("Node " + _nodeName + " is not connected to any CAN Bus.", Logger::ERROR);
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
}