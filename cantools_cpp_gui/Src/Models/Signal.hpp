#pragma once

#include <vector>
#include "CANSignal.hpp"
#include "IBusObserver.hpp"

class Signal : public cantools_cpp::CANSignal
{
public:
	void addObserver(IBusObserver* observer);
	void removeObserver(IBusObserver* observer);

private:
	void notifyObserver();

	std::vector<IBusObserver* > _observer;

};