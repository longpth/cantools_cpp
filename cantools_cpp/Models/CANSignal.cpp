/**
 * @file CANSignal.cpp
 * @brief Implementation of the CANSignal class for handling CAN message signals, decoding values, and notifying observers.
 * @author: Long Pham
 * @date: 10/02/2024
 */

#include "CANSignal.hpp"
#include "CANMessage.hpp"
#include "Logger.hpp"
#include "Util.hpp"

namespace cantools_cpp
{
    /**
     * @brief Constructor for CANSignal.
     * @param name The name of the signal.
     * @param startBit The starting bit position of the signal.
     * @param length The length of the signal in bits.
     * @param factor Scaling factor to convert raw value to physical value.
     * @param offset Offset to apply to the physical value after scaling.
     * @param minVal Minimum physical value for the signal.
     * @param maxVal Maximum physical value for the signal.
     * @param unit The unit of the signal (e.g., km/h, rpm).
     * @param byteOrder The byte order (MSB/LSB) of the signal.
     * @param valType The value type (signed, unsigned, float, double).
     * @param receiver The receiving node for this signal.
     * @param multiplexer The multiplexer group for this signal.
     */
    CANSignal::CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset, float minVal, float maxVal, std::string unit, uint8_t byteOrder, uint8_t valType, std::string receiver, std::string multiplexer)
        : _name(name), _startBit(startBit), _length(length), _factor(factor), _offset(offset), _minVal(minVal), _maxVal(maxVal), _unit(unit), _byteOrder(byteOrder), _receiver(receiver), _rawValue(0), _valueType(DbcValueType(valType)), _multiplexer(multiplexer)
    {
        _physicalValue = static_cast<double>(_rawValue) * _factor + _offset;
    }

    // Getters
    std::string CANSignal::getName() const { return _name; }
    uint8_t CANSignal::getStartBit() const { return _startBit; }
    uint8_t CANSignal::getLength() const { return _length; }
    float CANSignal::getFactor() const { return _factor; }
    float CANSignal::getOffset() const { return _offset; }
    uint64_t CANSignal::getRawValue() const { return _rawValue; }
    double CANSignal::getPhysicalValue() const { return _physicalValue; }
    DbcValueType CANSignal::getValueType() const { return _valueType; }
    uint8_t CANSignal::getByteOrder() const { return _byteOrder; }
    float CANSignal::getMinVal() const { return _minVal; }
    float CANSignal::getMaxVal() const { return _maxVal; }
    std::string CANSignal::getUnit() const { return _unit; }
    std::string CANSignal::getReceiver() const { return _receiver; }
    std::string CANSignal::getMultiplexer() const { return _multiplexer; }

    // Setters
    void CANSignal::setName(const std::string& name) { _name = name; }
    void CANSignal::setStartBit(uint8_t startBit) { _startBit = startBit; }
    void CANSignal::setLength(uint8_t length) { _length = length; }
    void CANSignal::setFactor(float factor) { _factor = factor; }
    void CANSignal::setOffset(float offset) { _offset = offset; }

    /**
     * @brief Sets the raw value of the signal and calculates the physical value.
     * @param value The raw signal value.
     */
    void CANSignal::setRawValue(uint64_t value) {
        _rawValue = value;
        // Calculate the physical value based on the factor and offset
        _physicalValue = static_cast<double>(_rawValue) * _factor + _offset;
        _parent.lock()->pack();
    }

    /**
     * @brief Sets the physical value and calculates the corresponding raw value.
     * @param value The physical signal value.
     */
    void CANSignal::setPhysicalValue(double value) {
        _physicalValue = value;
        // Calculate the raw value based on the physical value, factor, and offset
        _rawValue = static_cast<uint64_t>(((_physicalValue - _offset) / _factor));
        _parent.lock()->pack();
    }

    void CANSignal::setValueType(DbcValueType valueType) { _valueType = valueType; }

    /**
     * @brief Displays the signal name and raw value using the Logger.
     */
    void CANSignal::display() const {
        Logger::getInstance().log("Signal: " + _name + ", Value: " + std::to_string(_rawValue), Logger::LOG_INFO);
    }

    /**
     * @brief Sets the parent CANMessage for the signal.
     * @param parent A weak pointer to the parent CANMessage.
     */
    void CANSignal::setParent(std::weak_ptr<CANMessage> parent)
    {
        _parent = parent;
    }

    std::weak_ptr<CANMessage> CANSignal::getParent() const {
        return _parent;
    }

    /**
     * @brief Decodes the raw data and updates the signal's raw and physical values.
     * @param data Pointer to the raw CAN message data.
     */
    void CANSignal::decode(const uint8_t* data)
    {
        auto startBit = _startBit;

        // Get the length from the parent message
        auto parent = _parent.lock(); // Use lock to get a shared_ptr from weak_ptr
        if (!parent) {
            throw std::runtime_error("Parent message not available");
        }

        int length = parent->getLength();

        // Create a vector from the data with the length
        std::vector<uint8_t> tempArray(data, data + length);

        if (_byteOrder != ByteOrder_LSB)
        {
            // Reverse the array
            std::reverse(tempArray.begin(), tempArray.end());

            startBit = Util::getInstance().getStartBitLE(*this, length);
        }

        uint64_t rawValue = Util::getInstance().extractBits(tempArray, startBit, _length);

        if (_rawValue != rawValue)
        {
            _rawValue = rawValue;

            // Calculate the physical value using scaling and offset
            _physicalValue = _rawValue * _factor + _offset;

            notifyObserver();
        }
    }

    /**
     * @brief Encodes the signal's raw value into a byte vector based on the specified byte order.
     *
     * This function converts the signal's raw value into a vector of bytes. The encoding
     * is done according to the byte order (Little Endian or Big Endian) specified in the
     * _byteOrder member variable. The encoded bytes are placed in the correct positions
     * in the resulting vector based on the start bit and length of the signal.
     *
     * @return A vector of bytes representing the encoded signal value.
     */
    std::vector<uint8_t> CANSignal::encode() {
        std::vector<uint8_t> ret(_parent.lock()->getLength(), 0);

        // Encode the raw value based on the byte order
        if (_byteOrder == ByteOrder_LSB) {
            // Little Endian encoding
            for (uint8_t i = 0; i < _length; ++i) {
                // Set the value in the correct byte position
                ret[_startBit / 8 + i] |= static_cast<uint8_t>((_rawValue >> (8 * i)) & 0xFF);
            }
        }
        else {
            // Big Endian encoding
            auto startBit = Util::getInstance().getStartBitLE(*this, _length);
            for (uint8_t i = 0; i < _length; ++i) {
                // Set the value in the correct byte position
                ret[startBit / 8 + i] |= static_cast<uint8_t>((_rawValue >> (8 * i)) & 0xFF);
            }
            ret = Util::getInstance().mirrorMsg(ret);
        }

        return ret;
    }


    /**
     * @brief Adds an observer for the signal.
     * @param observer A pointer to an object implementing IBusObserver.
     */
    void CANSignal::addObserver(IBusObserver* observer)
    {
        _observers.push_back(observer);
    }

    /**
     * @brief Removes an observer for the signal.
     * @param observer A pointer to the observer to remove.
     */
    void CANSignal::removeObserver(IBusObserver* observer)
    {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    /**
     * @brief Notifies all observers of changes to the signal.
     */
    void CANSignal::notifyObserver()
    {
        for (auto observer : _observers)
        {
            observer->updateSignal(getParent().lock()->getId(), getName());
        }
    }

}
