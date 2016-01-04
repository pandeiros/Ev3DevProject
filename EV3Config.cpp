#include "EV3Config.h"

#include <iostream>
#include "ColorUtils.h"

namespace ev3 = ev3dev;

EV3Config::EV3Config() { }

EV3Config::EV3Config(const EV3Config & orig) { }

EV3Config::~EV3Config() { }

void EV3Config::printDeviceStatus()
{
    typedef ColorUtils COL;

    if (_sensors.size() == 0 || _motors.size() == 0)
        checkDevices();

    std::cout << "\033[2J\033[100A\n>>> DEVICE STATUS <<<\n";

    std::cout << "\n--- Battery ---\n";
    std::cout << "Voltage: " << ev3::power_supply::battery.measured_volts() << " V\n";
    std::cout << "Current: " << ev3::power_supply::battery.measured_amps() << " A\n";

    std::cout << "\n--- Sensors ---\n";
    for (int i = 0; i < INPUTS.size(); ++i)
    {
        std::cout << INPUTS[i] << ": ";

        bool found = false;
        for (auto & s : _sensors)
        {
            if (s.port_name() == INPUTS[i])
            {
                std::cout << COL::GREEN_BOLD << "connected. " << COL::RESET << "Type: " << s.type_name() << "\n";
                found = true;
            }

            _ports.insert({INPUTS[i], found});
        }

        if (!found)
            std::cout << COL::RED_FAINT << "disconnected. \n" << COL::RESET;
    }

    std::cout << "\n--- Motors ---\n";
    for (int i = 0; i < OUTPUTS.size(); ++i)
    {
        std::cout << OUTPUTS[i] << ": ";

        bool found = false;
        for (auto & m : _motors)
        {
            if (m.port_name() == OUTPUTS[i])
            {
                std::cout << COL::GREEN_BOLD << "connected. " << COL::RESET << "Type: " << m.type_name() << "\n";
                found = true;
            }
        }

        if (!found)
            std::cout << COL::RED_FAINT << "disconnected. \n" << COL::RESET;
    }

    std::cout << "\n(press ENTER to continue...)";
    std::cin.get();
}

void EV3Config::checkDevices()
{
    typedef ColorUtils COL;

    _devicesChecked = true;
    _sensors.clear();
    _motors.clear();

    // Check input devices.
    for (auto & input : INPUTS)
    {
        std::cout << COL::BLUE << "\n=== Checking input : " << COL::BLUE_BOLD << input << COL::RESET
                << COL::BLUE << " ===\n" << COL::RESET;

        auto ultrasonic_sensor = ev3::ultrasonic_sensor(input);
        if (ultrasonic_sensor.connected())
        {
            _sensors.push_back(ultrasonic_sensor);
            continue;
        }

        auto touch_sensor = ev3::touch_sensor(input);
        if (touch_sensor.connected())
        {
            _sensors.push_back(touch_sensor);
            continue;
        }

        auto color_sensor = ev3::color_sensor(input);
        if (color_sensor.connected())
        {
            _sensors.push_back(color_sensor);
            continue;
        }

        auto gyro_sensor = ev3::gyro_sensor(input);
        if (gyro_sensor.connected())
        {
            _sensors.push_back(gyro_sensor);
            continue;
        }

        auto infrared_sensor = ev3::infrared_sensor(input);
        if (infrared_sensor.connected())
        {
            _sensors.push_back(infrared_sensor);
            continue;
        }

        auto sound_sensor = ev3::sound_sensor(input);
        if (sound_sensor.connected())
        {
            _sensors.push_back(sound_sensor);
            continue;
        }

        auto light_sensor = ev3::light_sensor(input);
        if (light_sensor.connected())
        {
            _sensors.push_back(light_sensor);
            continue;
        }
    }

    // Check output devices.
    for (auto & output : OUTPUTS)
    {
        std::cout << COL::BLUE << "\n\n=== Checking output : " << COL::BLUE_BOLD << output << COL::RESET
                << COL::BLUE << " ===\n" << COL::RESET;

        auto largeMotor = ev3::large_motor(output);
        if (largeMotor.connected())
        {
            _motors.push_back(largeMotor);
            continue;
        }

        auto mediumMotor = ev3::medium_motor(output);
        if (mediumMotor.connected())
        {
            _motors.push_back(mediumMotor);
            continue;
        }
    }
}

