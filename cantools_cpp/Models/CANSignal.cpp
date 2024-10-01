#include "CANSignal.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{
    // Constructor
    CANSignal::CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset, float minVal, float maxVal, std::string unit, uint8_t byteOrder, uint8_t valType, std::string receiver, std::string multiplexer)
        : _name(name), _startBit(startBit), _length(length), _factor(factor), _offset(offset), _minVal(minVal), _maxVal(maxVal), _unit(unit), _byteOrder(byteOrder), _receiver(receiver), _value(0), _valueType(DbcValueType(valType)), _multiplexer(multiplexer)
    {

    }

    // Getters
    std::string CANSignal::getName() const { return _name; }
    uint8_t CANSignal::getStartBit() const { return _startBit; }
    uint8_t CANSignal::getLength() const { return _length; }
    float CANSignal::getFactor() const { return _factor; }
    float CANSignal::getOffset() const { return _offset; }
    uint64_t CANSignal::getValue() const { return _value; }
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
    void CANSignal::setValue(uint64_t value) { _value = value; }
    void CANSignal::setValueType(DbcValueType valueType) { _valueType = valueType; }

    // Display method
    void CANSignal::display() const {
        Logger::getInstance().log("Signal: " + _name + ", Value: " + std::to_string(_value), Logger::LOG_INFO);
    }

    void CANSignal::setParent(std::weak_ptr<CANMessage> parent)
    {
        _parent = parent;
    }

    std::weak_ptr<CANMessage> CANSignal::getParent() const {
        return _parent;
    }
}