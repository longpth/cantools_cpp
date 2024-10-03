/**
 * @file CANViewModel.hpp
 * @brief Declaration of the CANViewModel class for handling data and communication between the CAN network and the view.
 *
 * The CANViewModel class acts as an intermediary between the CAN network and the user interface. It observes
 * changes in the CAN bus and signals and notifies any registered views (observers) about updates. The view model
 * loads CAN data from a specified file and provides the necessary functionality to handle message and signal updates,
 * making it central to synchronizing CAN data with the user interface.
 *
 * The class also maintains a shared pointer to the BusManager, which manages the CAN buses and nodes. It encapsulates
 * the logic of notifying views of changes when messages or signals are updated and integrates the Parser to load
 * CAN-related data.
 *
 * @author Long Pham
 * @date 10/03/2024
 */

#pragma once

#include "TabDatabaseView.hpp"
#include "BusManager.hpp"
#include "IViewModelObserver.hpp"
#include "IView.hpp"
#include "Parser.hpp"

class TabDatabaseView;

/**
 * @class CANViewModel
 * @brief A class that observes changes in the CAN network and synchronizes data with the views.
 *
 * The CANViewModel class is responsible for managing the interaction between the CAN bus system and the views
 * that display CAN data. It loads CAN data, observes messages and signal changes, and notifies the registered
 * views (observers) about updates. This class ensures that the views are always in sync with the current state
 * of the CAN bus network.
 */
class CANViewModel : public IViewModelObserver
{
public:
    /**
     * @brief Constructs a CANViewModel instance.
     *
     * Initializes the bus manager and parser for handling CAN data and prepares the view model for observing
     * message and signal changes in the CAN network.
     */
    CANViewModel();

    /**
     * @brief Destructs the CANViewModel instance.
     */
    ~CANViewModel();

    /**
     * @brief Loads CAN data from a specified file path.
     *
     * The function loads the CAN data, such as message and signal definitions, from the given file using the parser.
     *
     * @param path The file path to the CAN data file (e.g., DBC or ARXML file).
     */
    void loadCANData(std::string path);

    /**
     * @brief Updates a specific CAN message in the view model.
     *
     * This function is called when a message in the CAN bus changes and needs to be updated in the view.
     *
     * @param busName The name of the bus where the message exists.
     * @param id The identifier of the CAN message to update.
     */
    void updateMessage(std::string busName, uint32_t id) override;

    /**
     * @brief Updates a specific CAN signal in the view model.
     *
     * This function is called when a signal in the CAN bus changes and needs to be updated in the view.
     *
     * @param busName The name of the bus where the signal exists.
     * @param id The identifier of the CAN message containing the signal.
     * @param signalName The name of the signal to update.
     */
    void updateSignal(std::string busName, uint32_t id, std::string signalName) override;

    /**
     * @brief Adds an observer to be notified of message and signal updates.
     *
     * Registers a view (observer) that will be notified whenever a message or signal in the CAN bus changes.
     *
     * @param view A pointer to the view (IView) to be notified.
     */
    void addObserver(IView* view);

    /**
     * @brief Retrieves the BusManager instance.
     *
     * Provides access to the BusManager, which manages the CAN buses and nodes.
     *
     * @return A shared pointer to the BusManager instance.
     */
    std::shared_ptr<BusManager> getBusMan() {
        return _busManager;
    }

private:

    /**
     * @brief Notifies all registered observers about a message change.
     *
     * This function is called internally to inform observers (views) that a message in the CAN bus has changed.
     *
     * @param busName The name of the bus where the message exists.
     * @param messageId The identifier of the CAN message that changed.
     */
    void notifyAboutMessageChange(std::string busName, uint32_t messageId);

    /**
     * @brief Notifies all registered observers about a signal change.
     *
     * This function is called internally to inform observers (views) that a signal in the CAN bus has changed.
     *
     * @param busName The name of the bus where the signal exists.
     * @param messageId The identifier of the CAN message containing the signal.
     * @param signalName The name of the signal that changed.
     */
    void notifyAboutSignalChange(std::string busName, uint32_t messageId, std::string signalName);

    std::shared_ptr<BusManager> _busManager;  ///< Shared pointer to the BusManager for managing CAN buses and nodes.
    std::unique_ptr<cantools_cpp::Parser> _parser; ///< Unique pointer to the Parser for loading CAN data.

    std::vector<IView*> _observers; ///< List of observers (views) to notify about changes.
};

