#include "Bus.hpp"

void Bus::updateMessage(uint32_t messageId)
{
	notifyObserverAboutMessage(messageId);
}
void Bus::updateSignal(uint32_t messageId, std::string signalName)
{
	notifyObserverAboutSignal(messageId, signalName);
}

void Bus::addObserver(IBusManagerObserver* observer)
{
	_observers.push_back(observer);
}

void Bus::removeObserver(IBusManagerObserver* observer)
{
	_observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}

void Bus::notifyObserverAboutMessage(uint32_t messageId)
{
	for (auto observer : _observers)
	{
		observer->updateMessage(getName(), messageId);
	}
}

void Bus::notifyObserverAboutSignal(uint32_t messageId, std::string signalName)
{
	for (auto observer : _observers)
	{
		observer->updateSignal(getName(), messageId, signalName);
	}
}