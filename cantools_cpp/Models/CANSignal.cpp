#include "CANSignal.hpp"
#include "CANMessage.hpp"
#include "Logger.hpp"
#include "Util.hpp"

namespace cantools_cpp
{
    // Constructor
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
    void CANSignal::setRawValue(uint64_t value) {
        _rawValue = value;
        // Calculate the physical value based on the factor and offset
        _physicalValue = static_cast<double>(_rawValue) * _factor + _offset;
    }
    void CANSignal::setPhysicalValue(double value) {
        _physicalValue = value;
        // Calculate the raw value based on the physical value, factor, and offset
        _rawValue = static_cast<uint64_t>(((_physicalValue - _offset) / _factor));
    }
    void CANSignal::setValueType(DbcValueType valueType) { _valueType = valueType; }

    // Display method
    void CANSignal::display() const {
        Logger::getInstance().log("Signal: " + _name + ", Value: " + std::to_string(_rawValue), Logger::LOG_INFO);
    }

    void CANSignal::setParent(std::weak_ptr<CANMessage> parent)
    {
        _parent = parent;
    }

    std::weak_ptr<CANMessage> CANSignal::getParent() const {
        return _parent;
    }

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

    void CANSignal::addObserver(IBusObserver* observer)
    {
        _observers.push_back(observer);
    }

    void CANSignal::removeObserver(IBusObserver* observer)
    {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    void CANSignal::notifyObserver()
    {
        for (auto observer : _observers)
        {
            observer->updateSignal(getParent().lock()->getId(), getName());
        }
    }

}