#include "Logger.hpp"

std::mutex Logger::mutex_;

Logger& Logger::getInstance() {
    static Logger instance;  // Guaranteed to be destroyed, instantiated on first use.
    return instance;
}

void Logger::log(const std::string& message, Level level) {
    std::lock_guard<std::mutex> lock(mutex_);  // Lock for thread safety
    if (level >= logLevel) {
        std::cout << "[" << levelToString(level) << "] " << message << std::endl;
    }
}

std::string Logger::levelToString(Level level) const {
    switch (level) {
    case INFO:    return "INFO";
    case WARNING: return "WARNING";
    case ERROR:   return "ERROR";
    default:      return "UNKNOWN";
    }
}
