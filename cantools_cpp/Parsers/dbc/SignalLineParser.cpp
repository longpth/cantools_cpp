#include <sstream>
#include "SignalLineParser.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    const std::regex SignalLineParser::signalRegex(
        R"regex(\s*SG_\s+([\w]+)\s*:\s*(\d+)\|(\d+)@([01])([+-])\s+\(([\d\+\-\.eE]+),([\d\+\-\.eE]+)\)\s+\[([\d\+\-\.eE]+)\|([\d\+\-\.eE]+)\]\s+"([^"]*)"\s+([\w\s,]+))regex"
    );

    SignalLineParser::SignalLineParser() {}

    bool SignalLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busManager, const std::string& busName) {
        std::smatch match;
        if (!std::regex_match(line, match, signalRegex)) {
            Logger::getInstance().log("Regex match failed for line: " + line, Logger::DEBUG);
            return false;
        }

        // Extract and construct a CANSignal from parsed data
        auto name = match[1].str();
        auto startBit = static_cast<uint8_t>(std::stoi(match[3].str()));
        auto length = static_cast<uint8_t>(std::stoi(match[4].str()));
        auto factor = std::stof(match[7].str());
        auto offset = std::stof(match[8].str());

        auto signal = std::make_shared<CANSignal>(name, startBit, length, factor, offset);

        busManager->getBus(busName)->addSignal(signal);

        Logger::getInstance().log("Signal added: " + name, Logger::DEBUG);
        return true;
    }

    bool SignalLineParser::isInteger(const std::string& str) {
        std::istringstream iss(str);
        int test;
        iss >> test;
        return iss.eof() && !iss.fail();
    }
}