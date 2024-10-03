/**
 * @file BusManager.hpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#pragma once

#include "CANBusManager.hpp"
#include "IViewModelObserver.hpp"
#include "IBusManagerObserver.hpp"

class BusManager : public cantools_cpp::CANBusManager, cantools_cpp::IBusManagerObserver
{
public:
	BusManager();

    void addObserver(IViewModelObserver* observer) {
        _observers.push_back(observer);
    }

    void removeObserver(IViewModelObserver* observer) {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    virtual void updateMessage(std::string busName, uint32_t messageId) override;
    virtual void updateSignal(std::string busName, uint32_t messageId, std::string signalName) override;

    virtual bool createBus(const std::string& busName) override;

private:
    void notifyObserversAboutMessage(std::string busName, uint32_t messageId);
    void notifyObserversAboutSignal(std::string busName, uint32_t messageId, std::string signalName);

    std::vector<IViewModelObserver*> _observers; // List of observers
};