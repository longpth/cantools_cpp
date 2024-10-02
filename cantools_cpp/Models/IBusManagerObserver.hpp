#pragma once
#include <string>

namespace cantools_cpp
{
	class IBusManagerObserver
	{
	public:
		virtual void updateMessage(std::string busName, uint32_t messageId) = 0;
		virtual void updateSignal(std::string busName, uint32_t messageId, std::string signalName) = 0;
	};
}