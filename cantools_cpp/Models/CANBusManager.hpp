// CANBusManager.hpp
#pragma once
#include <string>
#include <memory>
#include <unordered_map>

namespace cantools_cpp
{
    class CANBus;
    class CANMessage;
    class CANNode;

    class CANBusManager {
    private:
        std::unordered_map<std::string, std::shared_ptr<CANBus>> _busMap;

    public:
        CANBusManager();
        ~CANBusManager();

        virtual bool createBus(const std::string& busName);
        virtual std::shared_ptr<CANBus> getBus(const std::string& busName);
        virtual std::unordered_map<std::string, std::shared_ptr<CANBus>> getBuses()
        {
            return _busMap;
        }
    };
}