// CANBusManager.hpp
#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class CANBus;
class CANMessage;
class CANNode;

class CANBusManager {
private:
    std::unordered_map<std::string, std::shared_ptr<CANBus>> _busMap;

public:
    CANBusManager();
    ~CANBusManager();

    void createBus(const std::string& busName);
    std::shared_ptr<CANBus> getBus(const std::string& busName);
    std::unordered_map<std::string, std::shared_ptr<CANBus>> getBuses()
    {
        return _busMap;
    }
};
