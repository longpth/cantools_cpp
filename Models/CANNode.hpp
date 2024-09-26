// CANNode.h
#pragma once
#include <string>
#include <iostream>
#include "CANMessage.hpp"

class CANBusManager;
class CANBus;

class CANNode {
private:
    std::string _nodeName;
    std::shared_ptr<CANBus> _connectedBus;
    std::vector<std::shared_ptr<CANMessage>> _txMessages;

public:
    CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager);

    std::string getName() const {
        return _nodeName;
    }

    void addMessage(const std::shared_ptr<CANMessage>& msg);

    virtual void receiveMessage(const CANMessage& message);
    virtual void sendMessage(const CANMessage& message);
};