#pragma once

#include "CANBus.hpp"
#include "IBusObserver.hpp"
#include "IBusManagerObserver.hpp"

class Bus : public cantools_cpp::CANBus, IBusObserver
{
public:
	virtual void updateMessage(uint32_t messageId) override;
	virtual void updateSignal(uint32_t messageId, std::string signalName) override;

	void addObserver(IBusManagerObserver* observer);
	void removeObserver(IBusManagerObserver* observer);

private:
	void notifyObserverAboutMessage(uint32_t messageId);
	void notifyObserverAboutSignal(uint32_t messageId, std::string signalName);

	std::vector<IBusManagerObserver*> _observers;
};