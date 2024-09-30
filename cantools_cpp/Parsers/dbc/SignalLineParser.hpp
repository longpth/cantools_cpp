#pragma once
#include <regex>
#include <string>
#include <memory>
#include "ILineParser.hpp"
#include "CANBusManager.hpp"  // Assumes this class exists and can handle CANSignal
#include "CANSignal.hpp"      // Include the CANSignal header

namespace cantools_cpp
{

    class SignalLineParser : public ILineParser {
    public:
        SignalLineParser();

        virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busManager, const std::string& busName) override;

    private:
        static const std::regex signalRegex;
        static bool isInteger(const std::string& str);
    };

    // Regex pattern is defined in the .cpp file
}