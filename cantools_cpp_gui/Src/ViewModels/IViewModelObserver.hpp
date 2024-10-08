/**
 * @file IViewModelObserver.hpp
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#pragma once

class IViewModelObserver {
public:
    virtual ~IViewModelObserver() = default;
    virtual void updateMessage(std::string busName, uint32_t id) = 0;
    virtual void updateSignal(std::string busName, uint32_t id, std::string signalName) = 0;
};