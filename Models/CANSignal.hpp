// CANSignal.h
#pragma once
#include <string>
#include <iostream>

class CANSignal {
private:
    std::string _name;
    uint8_t _startBit;
    uint8_t _length;
    float _factor;
    float _offset;
    uint64_t _value;

public:
    CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset)
        : _name(name), _startBit(startBit), _length(length), _factor(factor), _offset(offset), _value(0) {}

    void setValue(uint64_t rawValue) {
        _value = rawValue;
    }

    uint64_t getValue() const {
        return _value;
    }

    void display() const {
        std::cout << "Signal: " << _name << " Value: " << _value << std::endl;
    }
};
