#pragma once
#include <string>

class IBusObserver
{
public:
	virtual void updateMessage(uint32_t messageId) = 0;
	virtual void updateSignal(uint32_t messageId, std::string signalName) = 0;
};