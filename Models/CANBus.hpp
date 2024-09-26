// CANBus.h
#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "CANNode.hpp"
#include "CANMessage.hpp"

class CANBus {
private:
    std::string _busName;
    std::vector<std::shared_ptr<CANNode>> _nodes; // Connected nodes
    std::vector<std::shared_ptr<CANMessage>> _allMessages;

public:
    CANBus(const std::string& name) : _busName(name) {}

    void addNode(const std::shared_ptr<CANNode>& node);

    void transmitMessage(const CANMessage& message);

    std::string getName() const;

    std::shared_ptr<CANNode> getNodeByName(const std::string& nodeName) const;

    void addMessage(const std::shared_ptr<CANMessage>& message);

    std::shared_ptr<CANMessage> getMessageById(const uint32_t id) const;
};
