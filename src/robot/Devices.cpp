#include "Devices.h"
#include "Utils.h"
#include "EventQueue.h"
#include "Logger.h"

using namespace ev3;

Devices * Devices::_instance = nullptr;

const ev3dev::port_type Devices::PORT_ANY{"any"};

Devices* Devices::getInstance()
{
    if (!_instance)
        _instance = new Devices;
    return _instance;
}

void Devices::update()
{
    // Update values;
    for (auto & sensor : _sensors)
    {
        for (unsigned int i = 0; i < sensor.second.getNumValues(); ++i)
        {
            _status[sensor.first][i].first = sensor.second.getValue(i);
            _status[sensor.first][i].second = sensor.second.getDecimals();
        }
    }

    for (auto & type : _listeners)
    {
        for (auto & sensor : _sensors)
        {
            if (sensor.second.getType() == type.first && type.second)
                EventQueue::getInstance()->push(
                    std::make_shared<EventSensorWatch>(type.first, _status[sensor.first]));
            type.second = false;
        }
    }

    // Check safety touch sensors.
//    unsigned int index = 0;
    for (auto & touch : _safetyTouchSensors)
    {
        if (_status.find(touch.first) != _status.end())
        {
            int oldValue = touch.second;
            int newValue = _status[touch.first][0].first;
            if (oldValue == 0 && newValue > 0)
                EventQueue::getInstance()->push(
                    std::make_shared<Event>(Event::OBSTACLE_DETECTED));

            touch.second = newValue;
        }
    }
    
    // Check proximity sensors
    for (auto & proximity : _proximitySensors)
    {
        if (_status.find(proximity.first) != _status.end())
        {
            int oldValue = proximity.second;
            int newValue = _status[proximity.first][0].first;
            Logger::getInstance()->log("Checking proximity " + 
            std::to_string(newValue), Logger::DEBUG);
        
            if (oldValue > 100 && newValue < 300)
                EventQueue::getInstance()->push(
                    std::make_shared<Event>(Event::PROXIMITY_ALERT));

            proximity.second = newValue;
        }
    }
}

void Devices::addListener(Sensor::SensorType type)
{
    _listeners[type] = true;
}

void Devices::setSafetyTouchSensor(ev3dev::port_type port)
{
    _safetyTouchSensors[port] = 1;
}

void Devices::setProximitySensor(ev3dev::port_type port)
{
    _proximitySensors[port] = 1;
}

void Devices::removeListener(Sensor::SensorType type)
{
    _listeners[type] = false;
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
        unsigned int temp = ready;
        for (auto & mapping : _motors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.getMotor().type_name() == device.second)
            {
                updateCountPerRot(mapping.second.getMotor().count_per_rot());
                Logger::getInstance()->log("Device connected: " + device.second + " at " +
                        device.first, Logger::VERBOSE);
                --ready;
                break;
            }
        }

        for (auto & mapping : _sensors)
        {
            if ((mapping.first == device.first || device.first == PORT_ANY) &&
                mapping.second.getSensor().driver_name() == device.second)
            {
                Logger::getInstance()->log("Device connected: " + device.second + " at " +
                        device.first, Logger::VERBOSE);
                --ready;
                break;
            }
        }

        if (temp == ready)
            Logger::getInstance()->log("Missing device: " + device.second + " at " +
                device.first, Logger::WARNING);
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
