#pragma once

#include <thread>

namespace ev3
{

    class LedControl
    {
    public:
        const static unsigned int MAX_BRIGHTNESS = 255;

        enum LedType
        {
            RED_L = 1,
            RED_R = 1 << 1,
            GREEN_L = 1 << 2,
            GREEN_R = 1 << 3,
            RED_ALL = RED_L | RED_R,
            GREEN_ALL = GREEN_L | GREEN_R,
            ALL = RED_ALL | GREEN_ALL,
        };

        enum LedColors
        {
            RED,
            AMBER,
            YELLOW,
            GREEN
        };

        virtual ~LedControl();

        void on(unsigned int leds = LedType::ALL, unsigned int brightness = MAX_BRIGHTNESS);
        void onExclusive(unsigned int leds = LedType::ALL, unsigned int brightness = MAX_BRIGHTNESS);
        void off(unsigned int leds = LedType::ALL);
        void setColor(LedColors color);
        void reset();

        // Repeat: 0 for infinite flashing.
        void flash(unsigned int leds, unsigned int msInterval, unsigned int repeat = 1,
                unsigned int brightnessRed = MAX_BRIGHTNESS, unsigned int brightnessGreen = MAX_BRIGHTNESS);
        void flashColor(LedColors color, unsigned int msInterval, unsigned int repeat = 1);

        void endFlashing();

    private:
        std::thread _flashThread;
        bool _isFlashingEnded;
    };
}