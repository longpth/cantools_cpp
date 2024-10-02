// CANBusManager.cpp
#include <iostream>
#include "CANBusManager.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    CANBusManager::CANBusManager() {
    }

    CANBusManager::~CANBusManager() {}

    bool CANBusManager::createBus(const std::string& busName) {
        bool ret = true;
        if (_busMap.find(busName) == _busMap.end()) {
            _busMap[busName] = std::make_shared<CANBus>(busName);
            Logger::getInstance().log("CAN Bus " + busName + " created.", Logger::LOG_INFO);
        }
        else {
            Logger::getInstance().log("CAN Bus " + busName + " already exists.", Logger::LOG_INFO);
            ret = false;
        }
        return ret;
    }

    std::shared_ptr<CANBus> CANBusManager::getBus(const std::string& busName) {
        if (_busMap.find(busName) != _busMap.end()) {
            return _busMap[busName];
        }
        else {
            Logger::getInstance().log("CAN Bus " + busName + " not found.", Logger::LOG_ERROR);
            return nullptr;
        }
    }
}