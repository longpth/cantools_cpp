/**
 * @file CANSignal.hpp
 * @brief Definition of the CANSignal class for handling CAN message signals.
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once
#include <string>
#include <memory>
#include <vector>
#include "IBusObserver.hpp"

namespace cantools_cpp
{
    class CANMessage;

    /**
     * @enum DbcValueType
     * @brief Specifies the value type of a CAN signal (signed, unsigned, or floating-point types).
     */
    enum DbcValueType
    {
        Signed,     ///< Signed integer value
        Unsigned,   ///< Unsigned integer value
        IEEEFloat,  ///< IEEE 754 single-precision floating-point value
        IEEEDouble  ///< IEEE 754 double-precision floating-point value
    };

    /**
     * @enum ByteOrder
     * @brief Specifies the byte order of a CAN signal.
     */
    enum ByteOrder
    {
        ByteOrder_MSB, ///< Most Significant Byte first (big-endian)
        ByteOrder_LSB  ///< Least Significant Byte first (little-endian)
    };

    /**
     * @class CANSignal
     * @brief Represents a signal within a CAN message. Handles signal decoding, value conversion, and observer notification.
     */
    class CANSignal {

    public:
        void addObserver(IBusObserver* observer);
        void removeObserver(IBusObserver* observer);

        // Constructor
        CANSignal(const std::string& name, uint8_t startBit, uint8_t length, float factor, float offset, float minVal, float maxVal, std::string unit, uint8_t byteOrder, uint8_t valType, std::string receiver, std::string multiplexer);

        // Getters
        std::string getName() const;
        uint8_t getStartBit() const;
        uint8_t getLength() const;
        float getFactor() const;
        float getOffset() const;
        uint64_t getRawValue() const;
        double getPhysicalValue() const;
        DbcValueType getValueType() const;
        std::weak_ptr<CANMessage> getParent() const;
        uint8_t getByteOrder() const;
        float getMinVal() const;
        float getMaxVal() const;
        std::string getUnit() const;
        std::string getReceiver() const;
        std::string getMultiplexer() const;

        // Setters
        void setName(const std::string& name);
        void setStartBit(uint8_t startBit);
        void setLength(uint8_t length);
        void setFactor(float factor);
        void setOffset(float offset);
        void setRawValue(uint64_t value);
        void setPhysicalValue(double value);
        void setValueType(DbcValueType val);

        // Display method
        void display() const;

        void setParent(std::weak_ptr<CANMessage> parent);

        void decode(const uint8_t* data);

        std::vector<uint8_t> encode();

    private:
        void notifyObserver();

        std::vector<IBusObserver*> _observers;

        std::string _name;
        uint16_t _startBit;
        uint16_t _length;
        float _factor;
        float _offset;
        uint64_t _rawValue;
        double _physicalValue;
        uint8_t _byteOrder;
        float _minVal;
        float _maxVal;
        std::string _unit;
        std::string _receiver;
        std::string _multiplexer;

        std::weak_ptr<CANMessage> _parent;

        DbcValueType _valueType;
    };
}
