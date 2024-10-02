/**
 * @file IBusManagerObserver.hpp
 * @brief
 *
 * @author Long Pham
 * @date 10/02/2024
 */

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