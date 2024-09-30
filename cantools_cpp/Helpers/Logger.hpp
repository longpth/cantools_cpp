#pragma once

#include <iostream>
#include <string>
#include <mutex>

class Logger {
public:
    enum Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance();
    void log(const std::string& message, Level level);

private:
    Logger() = default;  // Private constructor
    Logger(const Logger&) = delete;  // Prevent copying
    Logger& operator=(const Logger&) = delete;  // Prevent assignment

    static std::mutex mutex_;  // Mutex for thread safety
    Level logLevel = INFO;  // Default log level

    std::string levelToString(Level level) const;
};

