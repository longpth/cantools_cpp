#pragma once

#include <memory>
#include <sstream>
#include <iomanip>

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
        std::string ConvertToHexString(std::shared_ptr<uint8_t[]> data, size_t length) {
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

    private:
        // Private constructor to ensure singleton
        Util() = default;

        // Private destructor
        ~Util() = default;
    };
}