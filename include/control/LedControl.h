#pragma once

#include <thread>

namespace ev3
{
    /**
     * @class LedControl
     * Class specifically designed to eliminate ev3dev library
     * limitations of controlling LED panel.
     */
    class LedControl
    {
    public:
        /// Maximum value of brightness.
        const static unsigned int MAX_BRIGHTNESS = 255;

        /**
         * Type of LED diode.
         */
        enum LedType
        {
            RED_L = 1,                      /**< Red left diode. */
            RED_R = 1 << 1,                 /**< Red right diode. */
            GREEN_L = 1 << 2,               /**< Green left diode. */
            GREEN_R = 1 << 3,               /**< Green right diode. */
            RED_ALL = RED_L | RED_R,        /**< Both red diodes. */
            GREEN_ALL = GREEN_L | GREEN_R,  /**< Both green diodes. */
            ALL = RED_ALL | GREEN_ALL,      /**< All four diodes. */
        };

        /**
         * Predefined colors, that particular combination of
         * diodes can represent.
         */
        enum LedColors
        {
            RED,    /**< Only red diode. */
            AMBER,  /**< Red with a little bit of green. */
            YELLOW, /**< Little red and full green. */
            GREEN   /**< Only green diode. */
        };

        /**
         * Default destructor.
         */
        virtual ~LedControl();

        /**
         * Turn the specified diodes on.
         * @param leds Combination of LedControl::LedType values.
         * @param brightness Value of brightness to be set.
         */
        void on(unsigned int leds = LedType::ALL, unsigned int brightness = MAX_BRIGHTNESS);
        
        /**
         * Turn the specified diodes on and also turn off the other ones.
         * @param leds Combination of LedControl::LedType values.
         * @param brightness Value of brightness to be set.
         */
        void onExclusive(unsigned int leds = LedType::ALL, unsigned int brightness = MAX_BRIGHTNESS);
        
        /**
         * Turn the specified diodes off.
         * @param leds Combination of LedControl::LedType values.
         */
        void off(unsigned int leds = LedType::ALL);
        
        /**
         * Set diodes to match particular color.
         * @param color Type of to be displayed.
         */
        void setColor(LedColors color);
        
        /**
         * Ends flashing and turns all diodes off.
         */
        void reset();

        /**
         * Orders diodes to flash with given interval.
         * @param leds Combination of LedControl::LedType values.
         * @param msInterval Flash interval in milliseconds.
         * @param repeat Number of iterations or 0 for infinite flashing.
         * @param brightnessRed Brightness of the red diodes.
         * @param brightnessGreen Brightness of the green diodes.
         */
        void flash(unsigned int leds, unsigned int msInterval, unsigned int repeat = 1,
                unsigned int brightnessRed = MAX_BRIGHTNESS, unsigned int brightnessGreen = MAX_BRIGHTNESS);
        
        /**
         * Orders dioded to flash a particular color with given interval.
         * @param color Type of color to be displayed.
         * @param msInterval Flash interval in milliseconds.
         * @param repeat Number of iterations or 0 for infinite flashing.
         */
        void flashColor(LedColors color, unsigned int msInterval, unsigned int repeat = 1);

        /**
         * Stops flashing.
         */
        void endFlashing();

    private:
        /// Parallel thread responsible for flashing.
        std::thread _flashThread;
        
        /// Synchronization variable indicating, when the flash has to end.
        bool _isFlashingEnded;
    };
}