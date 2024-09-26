#include "CANSignal.hpp"

// Constructor
CANSignal::CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset)
    : _name(name), _startBit(startBit), _length(length), _factor(factor), _offset(offset), _value(0) {}

// Getters
std::string CANSignal::getName() const { return _name; }
uint8_t CANSignal::getStartBit() const { return _startBit; }
uint8_t CANSignal::getLength() const { return _length; }
float CANSignal::getFactor() const { return _factor; }
float CANSignal::getOffset() const { return _offset; }
uint64_t CANSignal::getValue() const { return _value; }

// Setters
void CANSignal::setName(const std::string& name) { _name = name; }
void CANSignal::setStartBit(uint8_t startBit) { _startBit = startBit; }
void CANSignal::setLength(uint8_t length) { _length = length; }
void CANSignal::setFactor(float factor) { _factor = factor; }
void CANSignal::setOffset(float offset) { _offset = offset; }
void CANSignal::setValue(uint64_t value) { _value = value; }

// Display method
void CANSignal::display() const {
    Logger::getInstance().log("Signal: " + _name + ", Value: " + std::to_string(_value), Logger::INFO);
}

void CANSignal::setParent(std::shared_ptr<CANMessage> parent)
{
    _parent = parent;
}