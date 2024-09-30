// ExtraMessageLineParser.hpp
#pragma once
#include <regex>
#include <string>
#include <memory>
#include "ILineParser.hpp"
#include "CANBusManager.hpp"

namespace cantools_cpp
{

    class ExtraMessageLineParser : public ILineParser {
    private:
        static const std::string ExtraMessageTransmitterLineStarter;
        static const std::regex ExtraTransmitterRegex;

    public:
        // Constructor
        ExtraMessageLineParser() = default;

        // Overriding the tryParse function
        virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) override;
    };

}
