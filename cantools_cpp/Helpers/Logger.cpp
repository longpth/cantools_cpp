#include "Logger.hpp"

namespace cantools_cpp
{

    std::mutex Logger::mutex_;

    Logger& Logger::getInstance() {
        static Logger instance;  // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    void Logger::log(const std::string& message, LogLevel level) {
        std::lock_guard<std::mutex> lock(mutex_);  // Lock for thread safety
        if (level >= logLevel) {
            std::cout << "[" << levelToString(level) << "] " << message << std::endl;
        }
    }

    std::string Logger::levelToString(LogLevel level) const {
        switch (level) {
        case LOG_INFO:    return "INFO";
        case LOG_WARNING: return "WARNING";
        case LOG_ERROR:   return "ERROR";
        default:      return "UNKNOWN";
        }
    }
}