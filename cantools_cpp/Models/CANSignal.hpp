#pragma once
#include <string>
#include <memory>

namespace cantools_cpp
{
    class CANMessage;

    enum DbcValueType
    {
        Signed,
        Unsigned,
        IEEEFloat,
        IEEEDouble
    };

    enum ByteOrder
    {
        ByteOrder_MSB,
        ByteOrder_LSB
    };

    class CANSignal {
    private:
        std::string _name;
        uint8_t _startBit;
        uint8_t _length;
        float _factor;
        float _offset;
        uint64_t _value;
        uint8_t _byteOrder;
        float _minVal;
        float _maxVal;
        std::string _unit;
        std::string _receiver;
        std::string _multiplexer;

        std::weak_ptr<CANMessage> _parent;

        DbcValueType _valueType;

    public:
        // Constructor
        CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset, float minVal, float maxVal, std::string unit, uint8_t byteOrder, uint8_t valType, std::string receiver, std::string multiplexer);

        // Getters
        std::string getName() const;
        uint8_t getStartBit() const;
        uint8_t getLength() const;
        float getFactor() const;
        float getOffset() const;
        uint64_t getValue() const;
        DbcValueType getValueType() const;
        std::weak_ptr<CANMessage> getParent() const;
        uint8_t CANSignal::getByteOrder() const;
        float CANSignal::getMinVal() const;
        float CANSignal::getMaxVal() const;
        std::string getUnit() const;
        std::string getReceiver() const;
        std::string getMultiplexer() const;

        // Setters
        void setName(const std::string& name);
        void setStartBit(uint8_t startBit);
        void setLength(uint8_t length);
        void setFactor(float factor);
        void setOffset(float offset);
        void setValue(uint64_t value);
        void setValueType(DbcValueType val);

        // Display method
        void display() const;

        void setParent(std::weak_ptr<CANMessage> parent);
    };
}