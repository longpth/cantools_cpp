#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include <memory>
#include "SignalValueTypeLineParser.hpp"
#include "Logger.hpp"
#include "CANSignal.hpp"
#include "CANBus.hpp"

namespace cantools_cpp
{

    // Definition of the regex (in the .cpp file)
    const std::regex SignalValueTypeLineParser::signalValueTypeRegex(
        R"(SIG_VALTYPE_\s+(\d+)\s+([a-zA-Z_]\w*)\s*:\s*([0123])\s*;)"
    );

    SignalValueTypeLineParser::SignalValueTypeLineParser() {}

    bool SignalValueTypeLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busManager, const std::string& busName) {
        std::string cleanLine = line;  // Assume we trim elsewhere if necessary

        if (cleanLine.find("SIG_VALTYPE_ ") != 0)
            return false;

        std::smatch match;
        if (std::regex_match(cleanLine, match, signalValueTypeRegex)) {
            if (match.size() == 4) {  // Ensure all groups are captured
                uint32_t messageId = std::stoul(match[1].str());
                std::string signalName = match[2].str();
                uint32_t signalType = std::stoul(match[3].str());

                if (signalType == 1 || signalType == 2) {
                    DbcValueType valueType = (signalType == 1 ? IEEEFloat : IEEEDouble);
                    busManager->getBus(busName)->addSignalValueType(messageId, signalName, valueType);
                }
            }
        }
        else {
            return false;
        }

        return true;
    }
}