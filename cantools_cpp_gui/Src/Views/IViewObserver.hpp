#pragma once

class IViewObserver {
public:
    virtual ~IViewObserver() = default;
    virtual void Update(std::vector<std::shared_ptr<cantools_cpp::CANNode>> nodes, std::vector<std::shared_ptr<cantools_cpp::CANMessage>> messages, std::string busName) = 0; // Method to be called when the observable changes
    virtual void UpdateMessageGrid(std::string busName, uint32_t messageId) = 0;
    virtual void UpdateSignalGrid(std::string busName, uint32_t messageId, std::string signalName) = 0;
};