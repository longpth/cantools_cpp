#include "BusManager.hpp"
#include "CANBus.hpp"
#include "Logger.hpp"

BusManager::BusManager(){}

void BusManager::updateMessage(std::string busName, uint32_t messageId)
{
    cantools_cpp::Logger::getInstance().log("[BusManager][" + busName + "] Message " + std::to_string(messageId) + " is updated ");
    notifyObserversAboutMessage(busName, messageId);
}

void BusManager::updateSignal(std::string busName, uint32_t messageId, std::string signalName)
{
    cantools_cpp::Logger::getInstance().log("[BusManager][" + busName + "] Signal " + signalName + " from message " + std::to_string(messageId) + " is updated ");
    notifyObserversAboutSignal(busName, messageId, signalName);
}

void BusManager::notifyObserversAboutMessage(std::string busName, uint32_t messageId)
{
    for (IViewModelObserver* observer : _observers) {
        observer->updateMessage(busName, messageId); // Notify each observer
    }
}

void BusManager::notifyObserversAboutSignal(std::string busName, uint32_t messageId, std::string signalName)
{
    for (IViewModelObserver* observer : _observers) {
        observer->updateSignal(busName, messageId, signalName); // Notify each observer
    }
}

bool BusManager::createBus(const std::string& busName)
{
    bool ret = CANBusManager::createBus(busName);
    if (ret == true)
    {
        auto bus = getBus(busName);
        bus->addObserver(this);
    }
    return ret;
}