#include "Devices.h"
#include "Utils.h"

using namespace ev3;

Devices * Devices::_instance = nullptr;

const ev3dev::port_type Devices::PORT_ANY{"any"};

Devices* Devices::getInstance()
{
    if (!_instance)
        _instance = new Devices;
    return _instance;
}

void Devices::destroy()
{
    delete _instance;
    _instance = nullptr;
}

Motor Devices::getMotor(ev3dev::port_type port)
{
    return _motors.at(port);
}

Sensor Devices::getSensor(ev3dev::port_type port)
{
    return _sensors.at(port);
}

bool Devices::checkDevices(RequiredDevices & requiredDevices)
{
    _sensors.clear();
    _motors.clear();

    // Check input devices.
    for (auto & input : INPUTS)
    {
        auto ultrasonic_sensor = ev3dev::ultrasonic_sensor(input);
        if (ultrasonic_sensor.connected())
        {
            _sensors.insert({input, Sensor(ultrasonic_sensor, Sensor::ULTRASONIC)});
            continue;
        }

        auto touch_sensor = ev3dev::touch_sensor(input);
        if (touch_sensor.connected())
        {
            _sensors.insert({input, Sensor(touch_sensor, Sensor::TOUCH)});
            continue;
        }

        auto color_sensor = ev3dev::color_sensor(input);
        if (color_sensor.connected())
        {
            _sensors.insert({input, Sensor(color_sensor, Sensor::COLOR)});
            continue;
        }

        auto gyro_sensor = ev3dev::gyro_sensor(input);
        if (gyro_sensor.connected())
        {
            _sensors.insert({input, Sensor(gyro_sensor, Sensor::GYRO)});
            continue;
        }

        auto infrared_sensor = ev3dev::infrared_sensor(input);
        if (infrared_sensor.connected())
        {
            _sensors.insert({input, Sensor(infrared_sensor, Sensor::INFRARED)});
            continue;
        }

        auto sound_sensor = ev3dev::sound_sensor(input);
        if (sound_sensor.connected())
        {
            _sensors.insert({input, Sensor(sound_sensor, Sensor::SOUND)});
            continue;
        }

        auto light_sensor = ev3dev::light_sensor(input);
        if (light_sensor.connected())
        {
            _sensors.insert({input, Sensor(light_sensor, Sensor::LIGHT)});
            continue;
        }
    }

    // Check output devices.
    for (auto & output : OUTPUTS)
    {
        auto largeMotor = ev3dev::large_motor(output);
        if (largeMotor.connected())
        {
            _motors.insert({output, Motor(largeMotor)});
            continue;
        }

        auto mediumMotor = ev3dev::medium_motor(output);
        if (mediumMotor.connected())
        {
            _motors.insert({output, Motor(mediumMotor)});
            continue;
        }
    }

    // Check required devices.
    unsigned int ready = requiredDevices.size();
    for (auto & device : requiredDevices)
    {
        for (auto & mapping : _motors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.getMotor().type_name() == device.second)
            {
                updateCountPerRot(mapping.second.getMotor().count_per_rot());

                --ready;
            }
        }

        for (auto & mapping : _sensors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.getSensor().type_name() == device.second)
            {
                --ready;
            }
        }
    }

    // Allocate status values.
    if (!ready)
    {
        for (auto & sensor : _sensors)
        {
            for (unsigned int i = 0; i < sensor.second.getNumValues(); ++i)
                _status[sensor.first].push_back(
                    std::make_pair(sensor.second.getValue(i), sensor.second.getDecimals()));
        }
    }

    return !ready;
}

void Devices::stopAllDevices()
{
    for (auto & motor : _motors)
    {
        motor.second.getMotor().stop();
    }
}

Devices::Devices() { }

Devices::~Devices() { }
