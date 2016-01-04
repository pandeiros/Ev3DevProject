#pragma once

#include "ev3dev.h"
#include <vector>

namespace ev3 = ev3dev;

const std::vector<ev3dev::port_type> INPUTS = {ev3::INPUT_1, ev3::INPUT_2, ev3::INPUT_3, ev3::INPUT_4};
const std::vector<ev3dev::port_type> OUTPUTS = {ev3::OUTPUT_A, ev3::OUTPUT_B, ev3::OUTPUT_C, ev3::OUTPUT_D};

class EV3Config
{
public:
    EV3Config();
    EV3Config(const EV3Config& orig);
    virtual ~EV3Config();

    void printDeviceStatus();

    std::vector<ev3dev::sensor> getSensors()
    {
        return _sensors;
    };

    std::vector<ev3dev::motor> getMotors()
    {
        return _motors;
    };

private:
    void checkDevices();

    std::vector<ev3dev::sensor> _sensors;
    std::vector<ev3dev::motor> _motors;
    std::map<std::string, bool> _ports;

    bool _devicesChecked = false;
};

