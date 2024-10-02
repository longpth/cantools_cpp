#include "Message.hpp"

void Message::addObserver(IBusObserver* observer)
{
	_observers.push_back(observer);
}

void Message::removeObserver(IBusObserver* observer)
{
	_observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
}

void Message::setData(uint8_t* data, int length)
{
	CANMessage::setData(data, length);

}

void Message::notifyObserver()
{
	for (auto observer : _observers)
	{
		observer->updateMessage(getId());
	}
}