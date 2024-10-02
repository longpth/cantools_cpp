#pragma once

#include <vector>
#include "CANMessage.hpp"
#include "IBusObserver.hpp"


class Message : public cantools_cpp::CANMessage
{
public:

	void addObserver(IBusObserver* observer);
	void removeObserver(IBusObserver* observer);

	virtual void setData(uint8_t* data, int length) override;

private:

	void notifyObserver();

	std::vector<IBusObserver*> _observers;
};