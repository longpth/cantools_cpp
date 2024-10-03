/**
 * @file CANBus.cpp
 * @brief Implementation of the CANBus class for managing CAN nodes and messages in the CAN tools application.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    void CANBus::addNode(const std::shared_ptr<CANNode>& node) {
        _nodes.push_back(node);
    }

    void CANBus::transmitMessage(const CANMessage& message) {
        Logger::getInstance().log("Transmitting message on CAN Bus: " + _busName, Logger::LOG_INFO);
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
        // Check if a message with the same ID already exists
        auto it = std::find_if(_allMessages.begin(), _allMessages.end(),
            [&message](const std::shared_ptr<CANMessage>& m) {
                return m->getId() == message->getId();
            });
        if (it == _allMessages.end()) { // Message ID not found, add new message
            _allMessages.push_back(message);
            _currentMessage = message;
            _allSignals[_currentMessage->getId()] = std::vector<std::shared_ptr<CANSignal>>();
            message->addObserver(this);
        }
        else {
            // Optionally, handle the case where the message is a duplicate
            // For example, you could log this event or update the existing message
        }
    }

    void CANBus::addSignal(const std::shared_ptr<CANSignal>& signal) {
        if (_currentMessage) {
            signal->setParent(_currentMessage);
            auto it = std::find_if(_allSignals[_currentMessage->getId()].begin(), _allSignals[_currentMessage->getId()].end(), [&signal](const std::shared_ptr<CANSignal>& s) {
                return signal->getName() == s->getName();
                });
            if (_allSignals[_currentMessage->getId()].size() == 0 || it == _allSignals[_currentMessage->getId()].end())
            {
                _allSignals[_currentMessage->getId()].push_back(signal);
                signal->addObserver(this);
            }
        }
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

    void CANBus::addSignalValueType(uint32_t messageId, std::string signalName, DbcValueType type) {
        auto it = _allSignals.find(messageId);
        if (it != _allSignals.end())
        {
            auto it2 = std::find_if(_allSignals[messageId].begin(), _allSignals[messageId].end(), [signalName](const std::shared_ptr<CANSignal>& signal) { return signalName == signal->getName(); });
            if (it2 != _allSignals[messageId].end()) {
                (*it2)->setValueType(type);
            }
        }
    }

    std::vector<std::shared_ptr<CANMessage>> CANBus::getAllMessages()
    {
        return _allMessages;
    }

    void CANBus::build()
    {
        for (auto message : _allMessages)
        {
            uint32_t messageId = message->getId();

            std::map<uint32_t, std::vector<std::shared_ptr<CANSignal>>>::iterator it = _allSignals.find(messageId);

            if (it != _allSignals.end())
            {
                for (auto sinal : it->second)
                {
                    message->addSignal(sinal);
                }
            }
        }
    }

    void CANBus::updateMessage(uint32_t messageId)
    {
        notifyObserverAboutMessage(messageId);
    }

    void CANBus::updateSignal(uint32_t messageId, std::string signalName)
    {
        notifyObserverAboutSignal(messageId, signalName);
    }

    void CANBus::addObserver(IBusManagerObserver* observer)
    {
        _observers.push_back(observer);
    }

    void CANBus::removeObserver(IBusManagerObserver* observer)
    {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    void CANBus::notifyObserverAboutMessage(uint32_t messageId)
    {
        for (auto observer : _observers)
        {
            observer->updateMessage(getName(), messageId);
        }
    }

    void CANBus::notifyObserverAboutSignal(uint32_t messageId, std::string signalName)
    {
        for (auto observer : _observers)
        {
            observer->updateSignal(getName(), messageId, signalName);
        }
    }

}