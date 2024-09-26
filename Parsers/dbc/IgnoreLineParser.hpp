#pragma once
// IgnoreLineParser.hpp

#include "ILineParser.hpp"
#include <string>

class IgnoreLineParser : public ILineParser {
public:
    // Constructor
    IgnoreLineParser() = default;

    // Overriding the tryParse function
    virtual bool tryParse(const std::string& line, std::shared_ptr<CANBusManager> busMan, const std::string& busName) override;
};
