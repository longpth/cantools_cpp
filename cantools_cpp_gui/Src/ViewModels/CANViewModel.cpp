#include <wx/filename.h>
#include <filesystem>
#include "CANViewModel.hpp"
#include "CANBus.hpp"
#include "TabDatabaseView.hpp"

CANViewModel::CANViewModel():_busManager(std::make_shared<BusManager>()),
_parser(std::make_unique<cantools_cpp::Parser>(_busManager))
{
}

CANViewModel::~CANViewModel() {

}

void CANViewModel::loadCANData(std::string filePath)
{
    std::string busName = std::filesystem::path(filePath).stem().string();
    // Load database from file
    _parser->loadDBC(filePath);
    for (auto observer : _observers)
    {
        auto observerTabDataBaseView = dynamic_cast<TabDatabaseView*>(observer);

        if (observerTabDataBaseView) {
            auto bus = _busManager->getBus(busName);
            auto nodes = bus->getNodes();
            auto messages = bus->getAllMessages();
            observerTabDataBaseView->Update(nodes, messages, busName);
        }
    }
}

void CANViewModel::updateMessage(std::string busName, uint32_t id)
{
    notifyAboutMessageChange(busName, id);
}

void CANViewModel::updateSignal(std::string busName, uint32_t id, std::string signalName)
{
    notifyAboutSignalChange(busName, id, signalName);
}

void CANViewModel::addObserver(IView* view) {
    _observers.push_back(view);
}

void CANViewModel::notifyAboutMessageChange(std::string busName, uint32_t messageId)
{
    for (auto observer : _observers)
    {
        auto observerTabDataBaseView = dynamic_cast<TabDatabaseView*>(observer);

        if (observerTabDataBaseView) {
            observerTabDataBaseView->UpdateMessageGrid(busName, messageId);
        }
    }
}
void CANViewModel::notifyAboutSignalChange(std::string busName, uint32_t messageId, std::string signalName)
{
    for (auto observer : _observers)
    {
        auto observerTabDataBaseView = dynamic_cast<TabDatabaseView*>(observer);

        if (observerTabDataBaseView) {
            observerTabDataBaseView->UpdateSignalGrid(busName, messageId, signalName);
        }
    }
}
