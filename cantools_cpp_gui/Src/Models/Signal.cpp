#include "Signal.hpp"
#include "CANMessage.hpp"

void Signal::addObserver(IBusObserver* observer)
{
	_observer.push_back(observer);
}

void Signal::removeObserver(IBusObserver* observer)
{
	_observer.erase(std::remove(_observer.begin(), _observer.end(), observer), _observer.end());
}

void Signal::notifyObserver()
{
	for (auto observer : _observer)
	{
		observer->updateSignal(getParent().lock()->getId(), getName());
	}
}