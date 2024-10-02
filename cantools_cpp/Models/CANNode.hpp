/**
 * @file CANNode.hpp
 * @brief Declaration of the CANNode class for representing a node in the CAN network.
 *
 * The CANNode class models a node that can communicate over a CAN bus. Each node is identified by a unique
 * name and can send and receive CAN messages. The class provides functionality to attach the node to a
 * specific CAN bus, manage transmitted messages, and facilitate communication with other nodes in the
 * network. By maintaining a weak reference to its connected CANBus, the CANNode prevents circular
 * dependencies while still being able to interact with the bus it is attached to.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once

#include <string>
#include <iostream>
#include "CANMessage.hpp"

namespace cantools_cpp
{
    class CANBusManager; ///< Forward declaration of the CANBusManager class.
    class CANBus; ///< Forward declaration of the CANBus class.

    class CANNode : public std::enable_shared_from_this<CANNode> {
    private:
        std::string _nodeName; ///< The name of the CAN node.
        std::weak_ptr<CANBus> _connectedBus; ///< Weak reference to the CANBus this node is attached to.
        std::vector<std::shared_ptr<CANMessage>> _txMessages; ///< List of messages to be transmitted by this node.

        bool _isAttachedToBus; ///< Flag indicating whether the node is attached to a CAN bus.

    public:
        /**
         * @brief Constructor to initialize a CANNode with a name and associated CANBus.
         *
         * @param name The name of the CAN node.
         * @param busName The name of the CAN bus to which this node will be attached.
         * @param busManager Reference to the CANBusManager for managing bus interactions.
         */
        CANNode(const std::string& name, const std::string& busName, CANBusManager& busManager);

        /**
         * @brief Retrieves the name of the CAN node.
         *
         * @return The name of the node as a string.
         */
        std::string getName() const {
            return _nodeName;
        }

        /**
         * @brief Attaches the node to its connected CAN bus.
         *
         * This method establishes a connection between the node and the associated CANBus, allowing
         * communication over the bus.
         */
        void attachToBus();

        /**
         * @brief Adds a CANMessage to the transmission queue of this node.
         *
         * @param msg A shared pointer to the CANMessage to be added.
         */
        void addMessage(const std::shared_ptr<CANMessage>& msg);

        /**
         * @brief Receives a CANMessage from the bus.
         *
         * This method processes incoming messages sent to this node.
         *
         * @param message The CANMessage to be processed.
         */
        virtual void receiveMessage(const CANMessage& message);

        /**
         * @brief Sends a CANMessage over the connected bus.
         *
         * This method transmits the specified message to other nodes on the CAN bus.
         *
         * @param message The CANMessage to be sent.
         */
        virtual void sendMessage(const CANMessage& message);
    };

} // namespace cantools_cpp
