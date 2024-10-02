// CANMessage.h
#pragma once
#include <vector>
#include <memory>
#include <map>
#include "CANSignal.hpp"
#include "SignalGroup.hpp"

#include <iostream>

namespace cantools_cpp
{

    class CANMessage {
    private:
        uint32_t _id;
        std::vector<std::shared_ptr<CANSignal>> _signals;
        std::vector<std::shared_ptr<SignalGroup>> _signalGroups;
        std::string _name;
        int _dlc;
        std::string _transmitter;
        std::vector<std::string> _additionalTransmitters;
        static const uint8_t _dlc2datalength[];
        std::shared_ptr<uint8_t[]> _data;
        float _cycle;

    public:
        CANMessage(uint32_t id);

        void addSignal(const std::shared_ptr<CANSignal>& signal);

        void addSignalGroup(const std::shared_ptr<SignalGroup>& group);

        void display() const;

        uint32_t getId() const;

        std::string getName() const;

        std::string getTransmitter() const;

        std::vector<std::string> getAdditionalTransmitters() const;

        int getDlc() const;

        int getLength() const;

        std::vector<std::shared_ptr<CANSignal>> getSignals();

        float getCycle() const;

        void setId(uint32_t id);

        void setName(const std::string& name);

        void setTransmitter(const std::string& transmitter);

        void setAdditionalTransmitters(std::vector<std::string> addTransmitters);

        void setDlc(int dlc);

        void setCycle(float cycle);

        std::shared_ptr<uint8_t[]> getData();

        virtual void setData(uint8_t* data, int length);
    };

}