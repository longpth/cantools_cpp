// ILineParser.hpp
#pragma once
#include <string>
#include <memory>

namespace cantools_cpp
{
    // Forward declaration of interfaces to avoid circular dependencies
    class CANBusManager;

    class ILineParser {
    public:
        virtual ~ILineParser() = default;

        // Pure virtual function equivalent to an interface method
        virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) = 0;
    };
}