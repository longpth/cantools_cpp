#include <sstream>
#include "SignalLineParser.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{
    const std::regex SignalLineParser::signalRegex(
        R"regex(\s*SG_\s+([\w]+)\s*([Mm\d]*)\s*:\s*(\d+)\|(\d+)@([01])([+-])\s+\(([\d\+\-eE.]+),([\d\+\-eE.]+)\)\s+\[([\d\+\-eE.]+)\|([\d\+\-eE.]+)\]\s+"([^"]*)"\s+([\w\s,]+))regex"
    );

    SignalLineParser::SignalLineParser() {}

    bool SignalLineParser::tryParse(const std::string& line, std::shared_ptr<CANBusManager> busManager, const std::string& busName)
    {
        std::smatch match;
        if (!std::regex_match(line, match, signalRegex)) {
            Logger::getInstance().log("Regex match failed for line: " + line, Logger::LOG_DEBUG);
            return false;
        }

        // Extract signal components based on matched groups
        auto name = match[1].str();
        auto multiplexer = match[2].str();
        auto startBit = static_cast<uint8_t>(std::stoi(match[3].str()));
        auto length = static_cast<uint8_t>(std::stoi(match[4].str()));
        auto byteOrder = static_cast<uint8_t>(std::stoi(match[5].str()));  // 0 = MSB, 1 = LSB
        auto valueType = match[6].str() == "-" ? DbcValueType::Signed : DbcValueType::Unsigned;
        auto factor = std::stof(match[7].str());
        auto offset = std::stof(match[8].str());
        auto minVal = std::stof(match[9].str());
        auto maxVal = std::stof(match[10].str());
        auto unit = match[11].str();
        auto receiver = match[12].str(); // Can be multiple receivers

        // Create the CANSignal and add it to the bus manager
        auto signal = std::make_shared<CANSignal>(name, startBit, length, factor, offset, minVal, maxVal, unit, byteOrder, valueType, receiver, multiplexer);

        // Add signal to the bus
        busManager->getBus(busName)->addSignal(signal);

        Logger::getInstance().log("Signal added: " + name, Logger::LOG_DEBUG);
        return true;
    }

    bool SignalLineParser::isInteger(const std::string& str)
    {
        std::istringstream iss(str);
        int test;
        iss >> test;
        return iss.eof() && !iss.fail();
    }
}