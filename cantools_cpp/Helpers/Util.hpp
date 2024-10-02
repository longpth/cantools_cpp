/**
 * @file Util.hpp
 * @brief Utility class for handling CAN message operations, including bit extraction, endianness conversion, and hex string formatting.
 * @author: Long Pham
 * @date: 10/02/2024
 */

#pragma once

#include <memory>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <vector>
#include "CANSignal.hpp"

namespace cantools_cpp
{
    class Util {
    public:
        /**
         * @brief Singleton instance access method.
         * @return A reference to the single Util instance.
         */
        static Util& getInstance() {
            static Util instance;
            return instance;
        }

        // Deleted methods to ensure singleton behavior (no copies or assignments)
        Util(const Util&) = delete;
        Util& operator=(const Util&) = delete;

        /**
         * @brief Converts a shared_ptr of uint8_t array to a hex string.
         * @param data A shared pointer to an array of uint8_t.
         * @param length The length of the byte array.
         * @return A string representing the hex values of the data.
         */
        std::string convertToHexString(std::shared_ptr<uint8_t[]> data, size_t length) {
            std::ostringstream oss;
            for (size_t i = 0; i < length; ++i) {
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
                if (i < length - 1) {
                    oss << " ";
                }
            }
            return oss.str();
        }

        /**
         * @brief Calculates the start bit for a CAN signal in Little Endian format.
         * @param signal The CANSignal instance containing the start bit and length information.
         * @param messageByteCount The number of bytes in the CAN message.
         * @return The adjusted start bit for Little Endian interpretation.
         */
        uint16_t getStartBitLE(const CANSignal& signal, int messageByteCount = 8) {
            uint16_t startByte = static_cast<uint16_t>(signal.getStartBit() / 8);

            uint16_t result = static_cast<uint16_t>(
                8 * messageByteCount
                - signal.getLength()
                - (8 * startByte)
                - ((8 * (startByte + 1) - signal.getStartBit() - 1) % 8)
                );

            return result;
        }

        /**
         * @brief Extracts bits from a byte array.
         * @param data The byte array from which bits are extracted.
         * @param startBit The starting bit position.
         * @param length The number of bits to extract.
         * @return The extracted bits as a 64-bit integer.
         */
        uint64_t extractBits(const std::vector<uint8_t>& data, int startBit, int length) {
            uint64_t result = 0;
            int bitIndex = 0;

            for (int bitPos = startBit; bitPos < startBit + length; bitPos++) {
                int bytePos = bitPos / 8;
                int bitInByte = bitPos % 8;

                if (bytePos >= data.size())
                    break;

                bool bit = (data[bytePos] & (1 << bitInByte)) != 0;
                if (bit) {
                    result |= 1ULL << bitIndex;
                }

                bitIndex++;
            }

            return result;
        }

        /**
         * @brief Reverses the byte order of the provided message (endianness conversion).
         * @param msg A vector of bytes representing the message.
         * @return A vector of bytes with reversed order.
         */
        std::vector<uint8_t> mirrorMsg(std::vector<uint8_t> msg) {
            std::vector<uint8_t> mirroredMsg(msg.size());

            for (size_t i = 0; i < msg.size(); ++i) {
                mirroredMsg[i] = msg[msg.size() - 1 - i];
            }

            return mirroredMsg;
        }

        /**
         * @brief Converts a hex string into a vector of bytes.
         * @param hexString The string containing hex values.
         * @param splitter A string used to split the hex string (default is space).
         * @return A vector of bytes extracted from the hex string.
         */
        std::vector<uint8_t> convertFromHexString(const std::string& hexString, const std::string& splitter = " ") {
            std::vector<uint8_t> bytes;
            std::string token;
            std::istringstream stream(hexString);

            while (std::getline(stream, token, splitter[0])) {
                if (token.length() == 0) continue;
                uint8_t byte = static_cast<uint8_t>(std::stoi(token, nullptr, 16));
                bytes.push_back(byte);
            }

            return bytes;
        }

    private:
        // Private constructor to ensure singleton
        Util() = default;

        // Private destructor
        ~Util() = default;
    };
}
