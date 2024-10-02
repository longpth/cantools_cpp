/**
 * @file CANBusManager.hpp
 * @brief Declaration of the CANBusManager class for managing multiple CAN buses in the CAN tools application.
 *
 * @author Long Pham
 * @date 10/02/2024
 */

#pragma once

#include <string>
#include <memory>
#include <unordered_map>

namespace cantools_cpp
{
    class CANBus;
    class CANMessage;
    class CANNode;

    class CANBusManager {
    private:
        std::unordered_map<std::string, std::shared_ptr<CANBus>> _busMap; ///< Map of CANBus instances indexed by their names.

    public:
        /**
         * @brief Default constructor for CANBusManager.
         */
        CANBusManager();

        /**
         * @brief Destructor for CANBusManager.
         */
        ~CANBusManager();

        /**
         * @brief Creates a new CANBus with a given name.
         *
         * This method initializes a new CANBus instance and adds it to the internal map for management.
         *
         * @param busName The name of the CAN bus to be created.
         * @return true if the bus was successfully created; false if a bus with the same name already exists.
         */
        virtual bool createBus(const std::string& busName);

        /**
         * @brief Retrieves a CANBus by its name.
         *
         * This method searches for an existing CANBus instance in the internal map and returns it if found.
         *
         * @param busName The name of the CAN bus to retrieve.
         * @return A shared pointer to the CANBus if found; otherwise, nullptr.
         */
        virtual std::shared_ptr<CANBus> getBus(const std::string& busName);

        /**
         * @brief Retrieves all managed CAN buses.
         *
         * @return An unordered map containing all CANBus instances managed by this manager.
         */
        virtual std::unordered_map<std::string, std::shared_ptr<CANBus>> getBuses()
        {
            return _busMap;
        }
    };
} // namespace cantools_cpp
