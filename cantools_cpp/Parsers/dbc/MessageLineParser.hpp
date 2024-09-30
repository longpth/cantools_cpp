// MessageLineParser.hpp
#pragma once
#include <regex>
#include <string>
#include <memory>
#include "ILineParser.hpp"
#include "CANBusManager.hpp"

namespace cantools_cpp
{

    class MessageLineParser : public ILineParser {
    private:
        static const std::string MessageLineStarter;
        static const std::regex MessageRegex;

    public:
        // Constructor
        MessageLineParser() = default;

        // Overriding the tryParse function
        virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) override;
    };

}