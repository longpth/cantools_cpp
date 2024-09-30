#pragma once
#include <regex>
#include <string>
#include "ILineParser.hpp"
#include "CANBusManager.hpp"  // This includes CAN message and signal value type management

namespace cantools_cpp
{
    class SignalValueTypeLineParser : public ILineParser {
    public:
        SignalValueTypeLineParser();
        virtual ~SignalValueTypeLineParser() = default;

        virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) override;

    private:
        static const std::regex signalValueTypeRegex;
    };
}
