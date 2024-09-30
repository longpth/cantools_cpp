// CANNode.h
#pragma once
#include <string>
#include <iostream>
#include "CANMessage.hpp"

namespace cantools_cpp
{
    class CANBusManager;
    class CANBus;

    class CANNode: public std::enable_shared_from_this<CANNode> {
    private:
        std::string _nodeName;
        std::weak_ptr<CANBus> _connectedBus;
        std::vector<std::shared_ptr<CANMessage>> _txMessages;

        bool _isAttchedToBus;

    public:
        CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager);

        std::string getName() const {
            return _nodeName;
        }

        void attachToBus();

        void addMessage(const std::shared_ptr<CANMessage>& msg);

        virtual void receiveMessage(const CANMessage& message);
        virtual void sendMessage(const CANMessage& message);
    };
    
}