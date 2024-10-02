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
        // Singleton instance access method
        static Util& getInstance() {
            static Util instance;
            return instance;
        }

        // Deleted methods to ensure singleton behavior (no copies or assignments)
        Util(const Util&) = delete;
        Util& operator=(const Util&) = delete;

        // Utility method to convert shared_ptr<uint8_t[]> to hex string
        std::string convertToHexString(std::shared_ptr<uint8_t[]> data, size_t length) {
            std::ostringstream oss;
            for (size_t i = 0; i < length; ++i) {
                // Convert each byte to a two-digit hex value and add to the stream
                oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);

                // Add space between hex values
                if (i < length - 1) {
                    oss << " ";
                }
            }
            return oss.str();
        }

        /// <summary>
        /// Get start bit Little Endian
        /// </summary>
        uint16_t getStartBitLE(const CANSignal& signal, int messageByteCount = 8)
        {
            uint16_t startByte = static_cast<uint16_t>(signal.getStartBit() / 8);

            uint16_t result = static_cast<uint16_t>(
                8 * messageByteCount
                - signal.getLength()
                - (8 * startByte)
                - ((8 * (startByte + 1) - signal.getStartBit() - 1) % 8)
                );

            return result;
        }

        uint64_t extractBits(const std::vector<uint8_t>& data, int startBit, int length)
        {
            uint64_t result = 0;
            int bitIndex = 0;

            for (int bitPos = startBit; bitPos < startBit + length; bitPos++)
            {
                int bytePos = bitPos / 8;
                int bitInByte = bitPos % 8;

                if (bytePos >= data.size())
                    break;

                bool bit = (data[bytePos] & (1 << bitInByte)) != 0;
                if (bit)
                {
                    result |= 1ULL << bitIndex;
                }

                bitIndex++;
            }

            return result;
        }

        std::vector<uint8_t> convertFromHexString(const std::string& hexString, const std::string& splitter = " ") {
            std::vector<uint8_t> bytes;
            std::string token;
            std::istringstream stream(hexString);

            // Use the splitter to tokenize the hex string
            while (std::getline(stream, token, splitter[0])) {
                if (token.length() == 0) continue;  // Skip empty tokens if any
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