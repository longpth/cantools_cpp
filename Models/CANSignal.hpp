#pragma once
#include <string>
#include <memory>
#include "Logger.hpp"

class CANMessage;

class CANSignal {
private:
    std::string _name;
    uint8_t _startBit;
    uint8_t _length;
    float _factor;
    float _offset;
    uint64_t _value;

    std::shared_ptr<CANMessage> _parent;

public:
    // Constructor
    CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset);

    // Getters
    std::string getName() const;
    uint8_t getStartBit() const;
    uint8_t getLength() const;
    float getFactor() const;
    float getOffset() const;
    uint64_t getValue() const;

    // Setters
    void setName(const std::string& name);
    void setStartBit(uint8_t startBit);
    void setLength(uint8_t length);
    void setFactor(float factor);
    void setOffset(float offset);
    void setValue(uint64_t value);

    // Display method
    void display() const;

    void setParent(std::shared_ptr<CANMessage> parent);
};
