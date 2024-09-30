// Parser.cpp
#include <filesystem>
#include "Parser.hpp"
#include "NodeLineParser.hpp"
#include "IgnoreLineParser.hpp"
#include "MessageLineParser.hpp"
#include "ExtraMessageLineParser.hpp"
#include "SignalLineParser.hpp"
#include "Logger.hpp"

Parser::Parser(std::shared_ptr<CANBusManager> busManager)
    : _busManager(busManager) {// Transfer ownership with std::move

    auto nodeLineParserPtr = std::make_shared<NodeLineParser>();
    auto ignoreLineParserPtr = std::make_shared<IgnoreLineParser>();
    auto messageLineParserPtr = std::make_shared<MessageLineParser>();
    auto extraMessageLineParser = std::make_shared<ExtraMessageLineParser>();
    auto signalLineParser = std::make_shared <SignalLineParser>();

    _vLineParsers.push_back(std::move(nodeLineParserPtr));
    _vLineParsers.push_back(std::move(ignoreLineParserPtr));
    _vLineParsers.push_back(std::move(messageLineParserPtr));
    _vLineParsers.push_back(std::move(extraMessageLineParser));
    _vLineParsers.push_back(std::move(signalLineParser));
} 

bool Parser::loadDBC(const std::string& fileDir) {
    std::ifstream file(fileDir);
    Logger& logger = Logger::getInstance();

    if (!file.is_open()) {
        logger.log("Error: Could not open file " + fileDir, Logger::DEBUG);
        return false;
    }

    std::string busName = std::filesystem::path(fileDir).stem().string();
    _busManager->createBus(busName);

    std::string line;
    while (std::getline(file, line)) {
        // Check if the line is empty or contains only whitespace
        if (line.empty() || std::all_of(line.begin(), line.end(), isspace)) {
            continue;
        }

        // Process each valid line
        logger.log("Read line: " + line, Logger::DEBUG);

        for (auto parser : _vLineParsers) {
            if (parser->tryParse(line, _busManager, busName)) {
                break;
            }
        }
    }

    file.close();
    logger.log("Finished loading database from " + fileDir, Logger::DEBUG);
    return true;
}