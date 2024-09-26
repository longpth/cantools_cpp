#include "CANMessage.hpp"

CANMessage::CANMessage(uint32_t id) : _id(id) {}

void CANMessage::addSignal(const std::shared_ptr<CANSignal>& signal) {
    _signals.push_back(signal);
}

void CANMessage::addSignalGroup(const std::shared_ptr<SignalGroup>& group) {
    _signalGroups.push_back(group);
}

void CANMessage::display() const {
    std::cout << "Message ID: " << _id << std::endl;
    for (const auto& signal : _signals) {
        signal->display();
    }
    for (const auto& group : _signalGroups) {
        group->display();
    }
}

uint32_t CANMessage::getId() const { return _id; }

std::string CANMessage::getName() const {
    return _name;
}

std::string CANMessage::getTransmitter() const {
    return _transmitter;
}

int CANMessage::getDlc() const {
    return _dlc;
}

void CANMessage::setId(uint32_t id) {
    _id = id;
}

void CANMessage::setName(const std::string& name) {
    _name = name;
}

void CANMessage::setTransmitter(const std::string& transmitter) {
    _transmitter = transmitter;
}

void CANMessage::setDlc(int dlc) {
    _dlc = dlc;
}

std::vector<std::string> CANMessage::getAdditionalTransmitters() const
{
    return _additionalTransmitters;
}

void CANMessage::setAdditionalTransmitters(std::vector<std::string> addTransmitters)
{
    _additionalTransmitters = addTransmitters;
}
