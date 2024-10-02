/**
 * @file IBusObserver.hpp
 * @brief
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once
#include <string>

namespace cantools_cpp
{
	class IBusObserver
	{
	public:
		virtual void updateMessage(uint32_t messageId) = 0;
		virtual void updateSignal(uint32_t messageId, std::string signalName) = 0;
	};
}