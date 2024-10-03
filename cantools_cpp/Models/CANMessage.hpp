/**
 * @file CANMessage.hpp
 * @brief Declaration of the CANMessage class for handling CAN messages in a CAN bus system.
 *
 * The CANMessage class represents a single CAN message, encapsulating its properties such as
 * ID, Data Length Code (DLC), and associated signals. The class provides methods to manage
 * signals, encode data, notify observers of state changes, and display message information.
 * It integrates with a logging system to log operations and errors related to CAN message handling.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once

#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include "CANSignal.hpp"
#include "SignalGroup.hpp"
#include "IBusObserver.hpp"

namespace cantools_cpp {

    class CANMessage {
    public:
        /**
         * @brief Constructor to create a CAN message with a specified ID.
         *
         * @param id Unique identifier for the CAN message.
         */
        CANMessage(uint32_t id);

        /**
         * @brief Adds a signal to the CAN message.
         *
         * @param signal A shared pointer to the CANSignal to be added.
         */
        void addSignal(const std::shared_ptr<CANSignal>& signal);

        /**
         * @brief Adds a signal group to the CAN message.
         *
         * @param group A shared pointer to the SignalGroup to be added.
         */
        void addSignalGroup(const std::shared_ptr<SignalGroup>& group);

        /**
         * @brief Displays the details of the CAN message, including signals and signal groups.
         */
        void display() const;

        /**
         * @brief Retrieves the ID of the CAN message.
         *
         * @return The ID of the CAN message.
         */
        uint32_t getId() const;

        /**
         * @brief Retrieves the name of the CAN message.
         *
         * @return The name of the CAN message.
         */
        std::string getName() const;

        /**
         * @brief Retrieves the transmitter of the CAN message.
         *
         * @return The transmitter of the CAN message.
         */
        std::string getTransmitter() const;

        /**
         * @brief Retrieves any additional transmitters associated with the CAN message.
         *
         * @return A vector of additional transmitters.
         */
        std::vector<std::string> getAdditionalTransmitters() const;

        /**
         * @brief Retrieves the Data Length Code (DLC) of the CAN message.
         *
         * @return The DLC of the CAN message.
         */
        int getDlc() const;

        /**
         * @brief Retrieves the length of the message data based on the DLC.
         *
         * @return The length of the message data.
         */
        int getLength() const;

        /**
         * @brief Retrieves the signals associated with the CAN message.
         *
         * @return A vector of shared pointers to CANSignal objects.
         */
        std::vector<std::shared_ptr<CANSignal>> getSignals();

        /**
         * @brief Retrieves the cycle time for the CAN message.
         *
         * @return The cycle time.
         */
        float getCycle() const;

        /**
         * @brief Sets the ID of the CAN message.
         *
         * @param id The new ID of the CAN message.
         */
        void setId(uint32_t id);

        /**
         * @brief Sets the name of the CAN message.
         *
         * @param name The new name of the CAN message.
         */
        void setName(const std::string& name);

        /**
         * @brief Sets the transmitter of the CAN message.
         *
         * @param transmitter The new transmitter of the CAN message.
         */
        void setTransmitter(const std::string& transmitter);

        /**
         * @brief Sets additional transmitters associated with the CAN message.
         *
         * @param addTransmitters A vector of additional transmitters to set.
         */
        void setAdditionalTransmitters(std::vector<std::string> addTransmitters);

        /**
         * @brief Sets the Data Length Code (DLC) of the CAN message.
         *
         * @param dlc The new DLC of the CAN message.
         */
        void setDlc(int dlc);

        /**
         * @brief Sets the data length of the CAN message.
         *
         * @param dlc The new length of the CAN message.
         */
        void setLength(int length);

        /**
         * @brief Sets the cycle time for the CAN message.
         *
         * @param cycle The new cycle time.
         */
        void setCycle(float cycle);

        /**
         * @brief Retrieves the data of the CAN message.
         *
         * @return A shared pointer to the message data.
         */
        std::shared_ptr<uint8_t[]> getData();

        /**
         * @brief Sets the data for the CAN message.
         *
         * @param data Pointer to the data to set.
         * @param length Length of the data.
         */
        void setData(uint8_t* data, int length);

        /**
         * @brief Adds an observer to the CAN message for updates.
         *
         * @param observer Pointer to the observer to add.
         */
        void addObserver(IBusObserver* observer);

        /**
         * @brief Removes an observer from the CAN message.
         *
         * @param observer Pointer to the observer to remove.
         */
        void removeObserver(IBusObserver* observer);

        /**
         * @brief Packs the signals into the CAN message data.
         *
         * This function encodes the signals associated with the message and merges the
         * encoded data into the message data.
         */
        void pack();

        /**
         * @brief Retrieves a signal by name, returning a weak pointer.
         *
         * @param name The name of the signal to retrieve.
         * @return A weak pointer to the CANSignal if found, otherwise an empty weak pointer.
         */
        std::weak_ptr<CANSignal> getSignal(std::string name);

    private:
        /**
         * @brief Notifies all observers of the CAN message about changes.
         */
        void notifyObserver();

        // Member variables
        uint32_t _id;  ///< Unique identifier for the CAN message.
        std::vector<std::shared_ptr<CANSignal>> _signals;  ///< Signals associated with the CAN message.
        std::vector<std::shared_ptr<SignalGroup>> _signalGroups;  ///< Signal groups associated with the CAN message.
        std::string _name;  ///< Name of the CAN message.
        int _dlc;  ///< Data Length Code (DLC) of the CAN message.
        int _length; ///< Data Length of the CAN message.
        std::string _transmitter;  ///< Transmitter of the CAN message.
        std::vector<std::string> _additionalTransmitters;  ///< Additional transmitters for the CAN message.
        static const uint8_t _dlc2datalength[];  ///< Array to map DLC to data length.
        static const std::map<uint8_t, uint8_t> _datalength2dlc;  ///< Map data length to DLC.
        std::shared_ptr<uint8_t[]> _data;  ///< Pointer to the message data.
        float _cycle;  ///< Cycle time for the CAN message.

        std::vector<IBusObserver*> _observers;  ///< Observers for the CAN message.
    };

} // namespace cantools_cpp
