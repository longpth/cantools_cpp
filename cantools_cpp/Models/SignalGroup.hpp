/**
 * @file SignalGroup.hpp
 * @brief
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once
#include <vector>
#include <memory>
#include "CANSignal.hpp"

namespace cantools_cpp
{

    class SignalGroup {
    private:
        std::vector<std::shared_ptr<CANSignal>> _signals;
        std::string _groupName;

    public:
        SignalGroup(const std::string& name) : _groupName(name) {}

        void addSignal(const std::shared_ptr<CANSignal>& signal) {
            _signals.push_back(signal);
        }

        void display() const {
            for (const auto& signal : _signals) {
                signal->display();
            }
        }
    };
}
