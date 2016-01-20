#include "LedControl.h"
#include "ev3dev.h"

#include <iostream>

using namespace ev3;

LedControl::~LedControl()
{
    _isFlashingEnded = true;
    if (_flashThread.joinable())
        _flashThread.join();
}

void LedControl::on(unsigned int leds, unsigned int brightness)
{
    typedef ev3dev::led LED;
    
    if (leds & RED_L && LED::red_left.connected())
        LED::red_left.set_brightness(brightness);
    if (leds & RED_R && LED::red_right.connected())
        LED::red_right.set_brightness(brightness);
    if (leds & GREEN_L && LED::green_left.connected())
        LED::green_left.set_brightness(brightness);
    if (leds & GREEN_R && LED::green_right.connected())
        LED::green_right.set_brightness(brightness);
}

void LedControl::onExclusive(unsigned int leds, unsigned int brightness)
{
    this->on(leds, brightness);
    this->off(~leds);
}

void LedControl::off(unsigned int leds)
{
    typedef ev3dev::led LED;

    if (leds & RED_L && LED::red_left.connected())
        LED::red_left.off();
    if (leds & RED_R && LED::red_right.connected())
        LED::red_right.off();
    if (leds & GREEN_L && LED::green_left.connected())
        LED::green_left.off();
    if (leds & GREEN_R && LED::green_right.connected())
        LED::green_right.off();
}

void LedControl::setColor(LedColors color)
{
    switch (color)
    {
        case RED:
            this->onExclusive(RED_ALL, MAX_BRIGHTNESS);
            break;
        case AMBER:
            this->on(RED_ALL, MAX_BRIGHTNESS);
            this->on(GREEN_ALL, 150);
            break;
        case YELLOW:
            this->on(RED_ALL, 100);
            this->on(GREEN_ALL, MAX_BRIGHTNESS);
            break;
        case GREEN:
            this->onExclusive(GREEN_ALL, MAX_BRIGHTNESS);
            break;
        default:
            break;
    }
}

void LedControl::reset()
{
    this->endFlashing();
    this->off(ALL);
}

void LedControl::flash(unsigned int leds, unsigned int msInterval, unsigned int repeat,
                       unsigned int brightnessRed, unsigned int brightnessGreen)
{
    typedef ev3dev::led LED;
    this->off(ALL);

    if (!_isFlashingEnded)
    {
        this->endFlashing();
    }

    _isFlashingEnded = false;

    bool * stop = &_isFlashingEnded;

    this->_flashThread = std::thread{[ = ]()
        {
            if (repeat > 0)
            {
                for (unsigned int i = 0; i < repeat * 2; ++i)
                {
                    if (i % 2 == 0)
                    {
                        this->on(leds & RED_ALL, brightnessRed);
                        this->on(leds & GREEN_ALL, brightnessGreen);
                    }
                    else
                    {
                        this->off(leds);
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(msInterval / 2));
                }

                LED::red_left.off();
            }
            else
            {
                unsigned int i = 0;
                while (!(*stop))
                {
                    if (i % 2 == 0)
                    {
                        this->on(leds & RED_ALL, brightnessRed);
                        this->on(leds & GREEN_ALL, brightnessGreen);
                    }
                    else
                    {
                        this->off(leds);
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(msInterval / 2));
                    i = (i + 1) % 2;
                }
            }

        }};
}

void LedControl::flashColor(LedColors color, unsigned int msInterval, unsigned int repeat)
{
    unsigned int leds = 0;
    unsigned int redBrightness = MAX_BRIGHTNESS;
    unsigned int greenBrightness = MAX_BRIGHTNESS;

    switch (color)
    {
        case RED:
            leds = RED_ALL;
            greenBrightness = 0;
            break;
        case AMBER:
            leds = ALL;
            greenBrightness = 150;
            break;
        case YELLOW:
            leds = ALL;
            redBrightness = 100;
            break;
        case GREEN:
            leds = GREEN_ALL;
            redBrightness = 0;
            break;
        default:
            break;
    }

    this->flash(leds, msInterval, repeat, redBrightness, greenBrightness);
}

void LedControl::endFlashing()
{
    _isFlashingEnded = true;
    if (_flashThread.joinable())
        _flashThread.join();
}


