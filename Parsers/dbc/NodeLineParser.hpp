// NodeLineParser.hpp
#pragma once
#include <string>
#include <regex>
#include <memory>
#include "ILineParser.hpp"
#include "CANBusManager.hpp"

class NodeLineParser : public ILineParser {
private:
    static constexpr const char* NodeLineStarter = "BU_:";
    static const std::string NameGroup;
    std::regex _regex;

public:
    NodeLineParser();
    virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) override;
};