// CANBus.h
#pragma once
#include <map>
#include <memory>
#include <iostream>
#include "CANNode.hpp"
#include "CANMessage.hpp"
#include "IBusObserver.hpp"
#include "IBusManagerObserver.hpp"

namespace cantools_cpp
{
    class CANBus: public IBusObserver
    {

    public:
        CANBus(const std::string& name) : _busName(name) {}

        void addNode(const std::shared_ptr<CANNode>& node);

        void transmitMessage(const CANMessage& message);

        std::string getName() const;

        std::vector<std::shared_ptr<CANNode>> getNodes() {
            return _nodes;
        }

        std::shared_ptr<CANNode> getNodeByName(const std::string& nodeName) const;

        void addMessage(const std::shared_ptr<CANMessage>& message);

        void addSignal(const std::shared_ptr<CANSignal>& signal);

        void addSignalValueType(uint32_t messageId, std::string signalName, DbcValueType type);

        std::shared_ptr<CANMessage> getMessageById(const uint32_t id) const;

        std::vector<std::shared_ptr<CANMessage>> getAllMessages();

        void build();

        virtual void updateMessage(uint32_t messageId) override;
        virtual void updateSignal(uint32_t messageId, std::string signalName) override;

        void addObserver(IBusManagerObserver* observer);
        void removeObserver(IBusManagerObserver* observer);

    private:
        void notifyObserverAboutMessage(uint32_t messageId);
        void notifyObserverAboutSignal(uint32_t messageId, std::string signalName);

        std::vector<IBusManagerObserver*> _observers;
        std::string _busName;
        std::vector<std::shared_ptr<CANNode>> _nodes; // Connected nodes
        std::vector<std::shared_ptr<CANMessage>> _allMessages;
        std::map<uint32_t, std::vector<std::shared_ptr<CANSignal>>> _allSignals;

        std::shared_ptr<CANMessage> _currentMessage;
    };
}
