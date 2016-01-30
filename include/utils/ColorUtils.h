#pragma once

#include <string>

class ColorUtils
{
public:
    typedef std::string colorCode;

    static const colorCode RED;
    static const colorCode GREEN;
    static const colorCode YELLOW;
    static const colorCode BLUE;

    static const colorCode RED_BOLD;
    static const colorCode GREEN_BOLD;
    static const colorCode YELLOW_BOLD;
    static const colorCode BLUE_BOLD;

    static const colorCode RED_FAINT;
    static const colorCode GREEN_FAINT;
    static const colorCode YELLOW_FAINT;
    static const colorCode BLUE_FAINT;
    static const colorCode WHITE_FAINT;

    static const colorCode RESET;
};

