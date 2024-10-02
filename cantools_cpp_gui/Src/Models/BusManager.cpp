#include "BusManager.hpp"

BusManager::BusManager(){}

void BusManager::updateMessage(std::string busName, uint32_t messageId)
{

}

void BusManager::updateSignal(std::string busName, uint32_t messageId, std::string signalName)
{

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