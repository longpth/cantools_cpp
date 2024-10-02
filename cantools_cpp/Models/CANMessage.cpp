#include "CANMessage.hpp"
#include "Logger.hpp"

namespace cantools_cpp
{

    const uint8_t CANMessage::_dlc2datalength[16] = {
    0 ,
    1 ,
    2 ,
    3 ,
    4 ,
    5 ,
    6 ,
    7 ,
    8 ,
    12 ,
    16 ,
    20 ,
    24 ,
    32 ,
    48 ,
    64
    };

    CANMessage::CANMessage(uint32_t id) : _id(id), _cycle(0) {}

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

    int CANMessage::getLength() const {
        return _dlc2datalength[_dlc];
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
        _data = std::shared_ptr<uint8_t[]>(new uint8_t[_dlc2datalength[dlc]]());
    }

    std::vector<std::string> CANMessage::getAdditionalTransmitters() const
    {
        return _additionalTransmitters;
    }

    void CANMessage::setAdditionalTransmitters(std::vector<std::string> addTransmitters)
    {
        _additionalTransmitters = addTransmitters;
    }

    void CANMessage::setCycle(float cycle)
    {
        _cycle = cycle;
    }

    float CANMessage::getCycle() const
    {
        return _cycle;
    }

    std::vector<std::shared_ptr<CANSignal>> CANMessage::getSignals()
    {
        return _signals;
    }

    std::shared_ptr<uint8_t[]> CANMessage::getData()
    {
        return _data;
    }

    std::weak_ptr<CANSignal> CANMessage::getSignal(std::string name)
    {
        std::weak_ptr<CANSignal> ptr;

        auto it = std::find_if(_signals.begin(), _signals.end(), [name](std::weak_ptr<CANSignal> signal) {
            return signal.lock()->getName() == name;
            }
        );

        if (it != _signals.end())
        {
            ptr = *it;
        }
        
        return ptr;
    }

    void CANMessage::setData(uint8_t* data, int length)
    {
        if (length > sizeof(_data))
        {
            Logger::getInstance().log("setData has invalid length", Logger::LOG_INFO);
        }
        for (int i = 0; i < length; i++) {
            _data[i] = data[i];
        }

        for (auto signal : _signals)
        {
            signal->decode(_data.get());
        }
    }

    void CANMessage::addObserver(IBusObserver* observer)
    {
        _observers.push_back(observer);
    }

    void CANMessage::removeObserver(IBusObserver* observer)
    {
        _observers.erase(std::remove(_observers.begin(), _observers.end(), observer), _observers.end());
    }

    void CANMessage::notifyObserver()
    {
        for (auto observer : _observers)
        {
            observer->updateMessage(getId());
        }
    }

}
