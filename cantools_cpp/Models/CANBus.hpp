/**
 * @file CANBus.hpp
 * @brief Declaration of the CANBus class for managing CAN nodes and messages in the CAN tools application.
 *
 * The CANBus class acts as a central component for managing connected CAN nodes and their
 * associated messages and signals. It implements the IBusObserver interface to receive
 * updates about messages and signals, facilitating communication within the CAN network.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once

#include <map>
#include <memory>
#include <iostream>
#include "CANNode.hpp"
#include "CANMessage.hpp"
#include "IBusObserver.hpp"
#include "IBusManagerObserver.hpp"

namespace cantools_cpp {

    class CANBus : public IBusObserver {
    public:
        /**
         * @brief Constructor to initialize the CANBus with a name.
         *
         * @param name The name of the CAN bus.
         */
        CANBus(const std::string& name) : _busName(name) {}

        /**
         * @brief Adds a CANNode to the bus.
         *
         * @param node A shared pointer to the CANNode to be added.
         */
        void addNode(const std::shared_ptr<CANNode>& node);

        /**
         * @brief Transmits a CANMessage over the bus.
         *
         * @param message The CANMessage to be transmitted.
         */
        void transmitMessage(const CANMessage& message);

        /**
         * @brief Retrieves the name of the CAN bus.
         *
         * @return The name of the bus as a string.
         */
        std::string getName() const;

        /**
         * @brief Retrieves all connected CAN nodes.
         *
         * @return A vector of shared pointers to connected CANNode instances.
         */
        std::vector<std::shared_ptr<CANNode>> getNodes() {
            return _nodes;
        }

        /**
         * @brief Gets a CANNode by its name.
         *
         * @param nodeName The name of the CANNode to retrieve.
         * @return A shared pointer to the CANNode if found; otherwise, nullptr.
         */
        std::shared_ptr<CANNode> getNodeByName(const std::string& nodeName) const;

        /**
         * @brief Adds a CANMessage to the bus.
         *
         * @param message A shared pointer to the CANMessage to be added.
         */
        void addMessage(const std::shared_ptr<CANMessage>& message);

        /**
         * @brief Adds a CANSignal to the current message on the bus.
         *
         * @param signal A shared pointer to the CANSignal to be added.
         */
        void addSignal(const std::shared_ptr<CANSignal>& signal);

        /**
         * @brief Adds a signal value type for a specific message ID.
         *
         * @param messageId The ID of the message.
         * @param signalName The name of the signal.
         * @param type The type of the signal value.
         */
        void addSignalValueType(uint32_t messageId, std::string signalName, DbcValueType type);

        /**
         * @brief Retrieves a CANMessage by its ID.
         *
         * @param id The ID of the CANMessage to retrieve.
         * @return A shared pointer to the CANMessage if found; otherwise, nullptr.
         */
        std::shared_ptr<CANMessage> getMessageById(const uint32_t id) const;

        /**
         * @brief Retrieves all messages on the bus.
         *
         * @return A vector of shared pointers to all CANMessage instances.
         */
        std::vector<std::shared_ptr<CANMessage>> getAllMessages();

        /**
         * @brief Builds the CAN bus with its components.
         */
        void build();

        // IBusObserver interface methods
        virtual void updateMessage(uint32_t messageId) override;

        virtual void updateSignal(uint32_t messageId, std::string signalName) override;

        /**
         * @brief Adds an observer to the bus manager.
         *
         * @param observer A pointer to the observer to add.
         */
        void addObserver(IBusManagerObserver* observer);

        /**
         * @brief Removes an observer from the bus manager.
         *
         * @param observer A pointer to the observer to remove.
         */
        void removeObserver(IBusManagerObserver* observer);

    private:
        /**
         * @brief Notifies observers about a message update.
         *
         * @param messageId The ID of the updated message.
         */
        void notifyObserverAboutMessage(uint32_t messageId);

        /**
         * @brief Notifies observers about a signal update.
         *
         * @param messageId The ID of the message containing the updated signal.
         * @param signalName The name of the updated signal.
         */
        void notifyObserverAboutSignal(uint32_t messageId, std::string signalName);

        std::vector<IBusManagerObserver*> _observers;  ///< List of observers for bus manager
        std::string _busName;                           ///< Name of the CAN bus
        std::vector<std::shared_ptr<CANNode>> _nodes; ///< Connected nodes
        std::vector<std::shared_ptr<CANMessage>> _allMessages; ///< All messages on the bus
        std::map<uint32_t, std::vector<std::shared_ptr<CANSignal>>> _allSignals; ///< Signals by message ID

        std::shared_ptr<CANMessage> _currentMessage;   ///< Current message being processed
    };

} // namespace cantools_cpp
