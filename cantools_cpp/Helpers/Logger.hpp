/**
 * @file Logger.hpp
 * @brief Declaration of the Logger class for logging messages in the CAN tools application.
 *
 * The Logger class provides a singleton implementation for logging messages at various
 * severity levels. It is designed to be thread-safe and offers methods to log messages
 * along with their associated log levels, ensuring consistent logging throughout the application.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once

#include <iostream>
#include <string>
#include <mutex>

namespace cantools_cpp {

    class Logger {
    public:
        // Enumeration for log levels
        enum LogLevel {
            LOG_DEBUG,    ///< Debug level for detailed logging.
            LOG_INFO,     ///< Info level for general information logging.
            LOG_WARNING,  ///< Warning level for potential issues.
            LOG_ERROR     ///< Error level for error messages.
        };

        /**
         * @brief Gets the singleton instance of the Logger class.
         *
         * @return Reference to the Logger instance.
         */
        static Logger& getInstance();

        /**
         * @brief Logs a message with a specified log level.
         *
         * @param message The message to log.
         * @param level The severity level of the message (default is LOG_DEBUG).
         */
        void log(const std::string& message, LogLevel level = LOG_DEBUG);

    private:
        Logger() = default;  // Private constructor to prevent instantiation
        Logger(const Logger&) = delete;  // Prevent copying
        Logger& operator=(const Logger&) = delete;  // Prevent assignment

        static std::mutex mutex_;  // Mutex for ensuring thread safety
        LogLevel logLevel = LOG_INFO;  // Default log level

        /**
         * @brief Converts log level enum to string for logging.
         *
         * @param level The log level to convert.
         * @return A string representation of the log level.
         */
        std::string levelToString(LogLevel level) const;
    };

} // namespace cantools_cpp
