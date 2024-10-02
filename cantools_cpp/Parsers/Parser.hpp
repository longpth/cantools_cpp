/**
 * @file Parser.hpp
 * @brief
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include "CANBusManager.hpp"
#include "ILineParser.hpp"

namespace cantools_cpp {
    class Parser {
    private:
        std::shared_ptr<CANBusManager> _busManager; // Use unique_ptr for CANBusManager
        std::vector<std::shared_ptr<ILineParser>> _vLineParsers;

    public:
        // Constructor that takes CANBusManager as a unique_ptr
        Parser(std::shared_ptr<CANBusManager> busManager);

        // Method to load data from the file line by line
        bool loadDBC(const std::string& fileDir);
    };
}