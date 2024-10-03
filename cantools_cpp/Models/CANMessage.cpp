/**
 * @file CANMessage.cpp
 * @brief Implementation of the CANMessage class for handling CAN messages, including adding signals,
 *        packing data, and notifying observers of message updates.
 *
 * The CANMessage class encapsulates the functionality to create and manipulate CAN messages, which
 * consist of various signals. It provides methods to encode the signals into the message's data,
 * manage signal groups, and notify observers of any changes in the message state. The class
 * utilizes a singleton logger for logging information and errors related to message operations.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#include "CANMessage.hpp"
#include "Logger.hpp"

namespace cantools_cpp {

    const uint8_t CANMessage::_dlc2datalength[16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8,
        12, 16, 20, 24, 32, 48, 64
    };

    const std::map<uint8_t, uint8_t> CANMessage::_datalength2dlc =
    {
        { 0, 0 },
        { 1, 1 },
        { 2, 2 },
        { 3, 3 },
        { 4, 4 },
        { 5, 5 },
        { 6, 6 },
        { 7, 7 },
        { 8, 8 },
        { 12, 9 },
        { 16, 10 },
        { 20, 11 },
        { 24, 12 },
        { 32, 13 },
        { 48, 14 },
        { 64, 15 },
    };

    /**
     * @brief Constructor for the CANMessage class, initializes the message ID and cycle.
     *
     * @param id The ID of the CAN message.
     */
    CANMessage::CANMessage(uint32_t id) : _id(id), _cycle(0) {}

    /**
     * @brief Adds a signal to the CAN message.
     *
     * @param signal A shared pointer to the CANSignal to be added.
     */
    void CANMessage::addSignal(const std::shared_ptr<CANSignal>& signal) {
        _signals.push_back(signal);
    }

    /**
     * @brief Adds a signal group to the CAN message.
     *
     * @param group A shared pointer to the SignalGroup to be added.
     */
    void CANMessage::addSignalGroup(const std::shared_ptr<SignalGroup>& group) {
        _signalGroups.push_back(group);
    }

    /**
     * @brief Displays the message ID and its associated signals and signal groups.
     */
    void CANMessage::display() const {
        std::cout << "Message ID: " << _id << std::endl;
        for (const auto& signal : _signals) {
            signal->display();
        }
        for (const auto& group : _signalGroups) {
            group->display();
        }
    }

    /**
     * @brief Retrieves the message ID.
     *
     * @return The ID of the CAN message.
     */
    uint32_t CANMessage::getId() const { return _id; }

    /**
     * @brief Retrieves the name of the CAN message.
     *
     * @return The name of the CAN message.
     */
    std::string CANMessage::getName() const {
        return _name;
    }

    /**
     * @brief Retrieves the transmitter of the CAN message.
     *
     * @return The transmitter of the CAN message.
     */
    std::string CANMessage::getTransmitter() const {
        return _transmitter;
    }

    /**
     * @brief Retrieves the Data Length Code (DLC) of the CAN message.
     *
     * @return The DLC of the CAN message.
     */
    int CANMessage::getDlc() const {
        return _dlc;
    }

    /**
     * @brief Retrieves the length of the message data based on the DLC.
     *
     * @return The length of the message data.
     */
    int CANMessage::getLength() const {
        return _length;
    }

    /**
     * @brief Sets the ID of the CAN message.
     *
     * @param id The new ID of the CAN message.
     */
    void CANMessage::setId(uint32_t id) {
        _id = id;
    }

    /**
     * @brief Sets the name of the CAN message.
     *
     * @param name The new name of the CAN message.
     */
    void CANMessage::setName(const std::string& name) {
        _name = name;
    }

    /**
     * @brief Sets the transmitter of the CAN message.
     *
     * @param transmitter The new transmitter of the CAN message.
     */
    void CANMessage::setTransmitter(const std::string& transmitter) {
        _transmitter = transmitter;
    }

    /**
     * @brief Sets the Data Length Code (DLC) of the CAN message and allocates memory for the data.
     *
     * @param dlc The new DLC of the CAN message.
     */
    void CANMessage::setDlc(int dlc) {
        _dlc = dlc;
        _data = std::shared_ptr<uint8_t[]>(new uint8_t[_dlc2datalength[dlc]]());
    }

    /**
     * @brief Sets the Data Length of the CAN message and allocates memory for the data.
     *
     * @param dlc The new data length of the CAN message.
     */
    void CANMessage::setLength(int length)
    {
        _dlc = _datalength2dlc.at(length);
        _length = length;
        _data = std::shared_ptr<uint8_t[]>(new uint8_t[length]());
    }

    /**
     * @brief Retrieves additional transmitters associated with the CAN message.
     *
     * @return A vector of additional transmitters.
     */
    std::vector<std::string> CANMessage::getAdditionalTransmitters() const {
        return _additionalTransmitters;
    }

    /**
     * @brief Sets additional transmitters associated with the CAN message.
     *
     * @param addTransmitters A vector of additional transmitters to set.
     */
    void CANMessage::setAdditionalTransmitters(std::vector<std::string> addTransmitters) {
        _additionalTransmitters = addTransmitters;
    }

    /**
     * @brief Sets the cycle time for the CAN message.
     *
     * @param cycle The new cycle time.
     */
    void CANMessage::setCycle(float cycle) {
        _cycle = cycle;
    }

    /**
     * @brief Retrieves the cycle time of the CAN message.
     *
     * @return The cycle time.
     */
    float CANMessage::getCycle() const {
        return _cycle;
    }

    /**
     * @brief Retrieves the signals associated with the CAN message.
     *
     * @return A vector of shared pointers to CANSignal objects.
     */
    std::vector<std::shared_ptr<CANSignal>> CANMessage::getSignals() {
        return _signals;
    }

    /**
     * @brief Retrieves the data of the CAN message.
     *
     * @return A shared pointer to the message data.
     */
    std::shared_ptr<uint8_t[]> CANMessage::getData() {
        return _data;
    }

    /**
     * @brief Retrieves a signal by name, returning a weak pointer.
     *
     * @param name The name of the signal to retrieve.
     * @return A weak pointer to the CANSignal if found, otherwise an empty weak pointer.
     */
    std::weak_ptr<CANSignal> CANMessage::getSignal(std::string name) {
        std::weak_ptr<CANSignal> ptr;

        auto it = std::find_if(_signals.begin(), _signals.end(), [name](std::weak_ptr<CANSignal> signal) {
            return signal.lock()->getName() == name;
            });

        if (it != _signals.end()) {
            ptr = *it;
        }

        return ptr;
    }

    /**
     * @brief Sets the data of the CAN message and decodes signals from the data.
     *
     * @param data Pointer to the data to set.
     * @param length Length of the data.
     */
    void CANMessage::setData(uint8_t* data, int length) {
        if (length > sizeof(_data)) {
            Logger::getInstance().log("setData has invalid length", Logger::LOG_INFO);
        }
        for (int i = 0; i < length; i++) {
            _data[i] = data[i];
        }

        for (auto signal : _signals) {
            signal->decode(_data.get());
        }
    }

    /**
     * @brief Adds an observer to the CAN message.
     *
     * @param observer Pointer to the observer to add.
     */
    void CANMessage::addObserver(IBusObserver* observer) {
        _observers.push_back(observer);
    }

    /**
     * @brief Removes an observer from the CAN message.
     *
     * @param observer Pointer to the observer to remove.
     */
    void CANMessage::removeObserver(IBusObserver* observer) {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    /**
     * @brief Notifies all observers of the CAN message about changes.
     */
    void CANMessage::notifyObserver() {
        for (auto observer : _observers) {
            observer->updateMessage(getId());
        }
    }

    /**
     * @brief Packs the signals into the message data using the bitwise OR operator.
     *
     * This function encodes each signal associated with the CAN message and merges the encoded
     * data into the message data. It then notifies observers of the message update.
     */
    void CANMessage::pack() {
        uint8_t length = _dlc2datalength[_dlc];
        // Initialize a vector to hold the packed message
        std::vector<uint8_t> packedData(length, 0);

        for (const auto& signal : _signals) {
            // Encode the signal
            std::vector<uint8_t> encodedData = signal->encode();

            // Merge the encoded data into the packedData using bitwise OR
            for (size_t i = 0; i < encodedData.size(); ++i) {
                packedData[i] |= encodedData[i];
            }
        }

        // Set the packed data to the CAN message
        for (size_t i = 0; i < packedData.size(); ++i) {
            _data[i] = packedData[i];
        }

        // Notify observers about the updated message
        notifyObserver();
    }

} // namespace cantools_cpp
