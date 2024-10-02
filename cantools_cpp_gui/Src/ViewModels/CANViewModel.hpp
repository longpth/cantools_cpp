#pragma once

#include "TabDatabaseView.hpp"
#include "BusManager.hpp"
#include "IViewModelObserver.hpp"
#include "IView.hpp"
#include "Parser.hpp"

class TabDatabaseView;

class CANViewModel : public IViewModelObserver
{
public:
    CANViewModel();

    ~CANViewModel();

    void loadCANData(std::string path);

    void updateMessage(std::string busName, uint32_t id) override;
    void updateSignal(std::string busName, uint32_t id, std::string signalName) override;

    // Add observers for message and signal updates
    void addObserver(IView* view);

    std::shared_ptr<BusManager> getBusMan() {
        return _busManager;
    }

private:

    void notifyAboutMessageChange(std::string busName, uint32_t messageId);
    void notifyAboutSignalChange(std::string busName, uint32_t messageId, std::string signalName);

    std::shared_ptr<BusManager> _busManager;  // Shared pointer to BusManager
    std::unique_ptr<cantools_cpp::Parser> _parser;              // Unique pointer to Parser

    std::vector<IView*> _observers;
};
