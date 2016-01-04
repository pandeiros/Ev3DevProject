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

void LedControl::flash(unsigned int msInterval, unsigned int repeat, unsigned int brightness)
{
    typedef ev3dev::led LED;
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
                        LED::red_left.set_brightness(brightness);
                    }
                    else
                    {
                        LED::red_left.off();
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
                        LED::red_left.set_brightness(brightness);
                    }
                    else
                    {
                        LED::red_left.off();
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(msInterval / 2));
                    i = (i + 1) % 2;
                }
            }

        }};
}

void LedControl::endFlashing()
{
    _isFlashingEnded = true;
    if (_flashThread.joinable())
        _flashThread.join();
}


