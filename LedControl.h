#pragma once

#include <thread>

namespace ev3
{

    class LedControl
    {
    public:

        enum LedType
        {
            RED_L = 1,
            RED_R = 1 << 1,
            GREEN_L = 1 << 2,
            GREEN_R = 1 << 3,
            RED_ALL = RED_L | RED_R,
            GREEN_ALL = GREEN_L | GREEN_R,
            ALL = RED_ALL | GREEN_ALL
        };
        
        virtual ~LedControl();

        void on(unsigned int leds = LedType::ALL, unsigned int brightness = 255);
        void onExclusive(unsigned int leds = LedType::ALL, unsigned int brightness = 255);
        void off(unsigned int leds = LedType::ALL);

        // Only one led can flash: red_left
        // Repeat: 0 for infinite flashing.
        void flash(unsigned int msInterval, unsigned int repeat = 1, unsigned int brightness = 255);

        void endFlashing();

    private:
        std::thread _flashThread;
        bool _isFlashingEnded;
    };
}