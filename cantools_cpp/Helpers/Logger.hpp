#pragma once

#include <iostream>
#include <string>
#include <mutex>

namespace cantools_cpp
{
    class Logger {
        public:
            enum LogLevel {
                LOG_DEBUG,
                LOG_INFO,
                LOG_WARNING,
                LOG_ERROR
            };
        
        static Logger& getInstance();
        void log(const std::string& message, LogLevel level= LOG_DEBUG);

        private:
            Logger() = default;  // Private constructor
            Logger(const Logger&) = delete;  // Prevent copying
            Logger& operator=(const Logger&) = delete;  // Prevent assignment

            static std::mutex mutex_;  // Mutex for thread safety
            LogLevel logLevel = LOG_INFO;  // Default log level

            std::string levelToString(LogLevel level) const;
    };
}

