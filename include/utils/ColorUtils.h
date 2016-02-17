#pragma once

#include <string>

namespace ev3
{
    /**
     * @class ColorUtils
     * Stores all available color escape codes.
     */
    class ColorUtils
    {
    public:
        /// Type for storing color names.
        typedef std::string colorCode;

        /// BLACK color code.
        static const colorCode BLACK;

        /// RED color code.
        static const colorCode RED;

        /// GREEN color code.
        static const colorCode GREEN;

        /// YELLOW color code.
        static const colorCode YELLOW;

        /// BLUE color code.
        static const colorCode BLUE;

        /// MAGENTA color code.
        static const colorCode MAGENTA;

        /// CYAN color code.
        static const colorCode CYAN;

        /// WHITE color code.
        static const colorCode WHITE;

        /// BLACK_BOLD color code.
        static const colorCode BLACK_BOLD;

        /// RED_BOLD color code.
        static const colorCode RED_BOLD;

        /// GREEN_BOLD color code.
        static const colorCode GREEN_BOLD;

        /// YELLOW_BOLD color code.
        static const colorCode YELLOW_BOLD;

        /// BLUE_BOLD color code.
        static const colorCode BLUE_BOLD;

        /// MAGENTA_BOLD color code.
        static const colorCode MAGENTA_BOLD;

        /// CYAN_BOLD color code.
        static const colorCode CYAN_BOLD;

        /// WHITE_BOLD color code.
        static const colorCode WHITE_BOLD;

        /// BLACK_FAINT color code.
        static const colorCode BLACK_FAINT;

        /// RED_FAINT color code.
        static const colorCode RED_FAINT;

        /// GREEN_FAINT color code.
        static const colorCode GREEN_FAINT;

        /// YELLOW_FAINT color code.
        static const colorCode YELLOW_FAINT;

        /// BLUE_FAINT color code.
        static const colorCode BLUE_FAINT;

        /// MAGENTA_FAINT color code.
        static const colorCode MAGENTA_FAINT;

        /// CYAN_FAINT color code.
        static const colorCode CYAN_FAINT;

        /// WHITE_FAINT color code.
        static const colorCode WHITE_FAINT;

        /// RESET color.
        static const colorCode RESET;

        /**
         * Print "TEST" in all available colors.
         */
        static void printColorTest();
    };
}
