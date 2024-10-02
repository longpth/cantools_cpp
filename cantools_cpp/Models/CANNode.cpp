/**
 * @file CANNode.cpp
 * @brief Declaration of the CANNode class for representing a node in the CAN network.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#include <string>
#include <algorithm>
#include "CANNode.hpp"
#include "CANBusManager.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    CANNode::CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager)
        : _nodeName(name), _isAttachedToBus(false) {
        _connectedBus = busManager.getBus(busName);
    }

    void CANNode::attachToBus()
    {
        auto bus = _connectedBus.lock();
        if (bus && !_isAttachedToBus) {
            bus->addNode(shared_from_this());
            Logger::getInstance().log("Node " + _nodeName + " connected to CAN Bus " + bus->getName(), Logger::LOG_INFO);
        }
    }

    void CANNode::receiveMessage(const CANMessage& message) {
        auto bus = _connectedBus.lock();
        Logger::getInstance().log("Node " + _nodeName + " received message ID: " + std::to_string(message.getId()) + " from Bus " + bus->getName(), Logger::LOG_INFO);
    }

    void CANNode::sendMessage(const CANMessage& message) {
        if (auto bus = _connectedBus.lock())
        {
            bus->transmitMessage(message);
        }
        else
        {
            Logger::getInstance().log("Node " + _nodeName + " is not connected to any CAN Bus.", Logger::LOG_ERROR);
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

            auto bus = _connectedBus.lock();

            bus->addMessage(msg);
        }
    }
}