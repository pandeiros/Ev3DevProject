#pragma once

#include <string>

namespace ev3 {

class ColorUtils
{
public:
    typedef std::string colorCode;

    static const colorCode BLACK;
    static const colorCode RED;
    static const colorCode GREEN;
    static const colorCode YELLOW;
    static const colorCode BLUE;
    static const colorCode MAGENTA;
    static const colorCode CYAN;
    static const colorCode WHITE;

    static const colorCode BLACK_BOLD;
    static const colorCode RED_BOLD;
    static const colorCode GREEN_BOLD;
    static const colorCode YELLOW_BOLD;
    static const colorCode BLUE_BOLD;
    static const colorCode MAGENTA_BOLD;
    static const colorCode CYAN_BOLD;
    static const colorCode WHITE_BOLD;
    
    static const colorCode BLACK_FAINT;
    static const colorCode RED_FAINT;
    static const colorCode GREEN_FAINT;
    static const colorCode YELLOW_FAINT;
    static const colorCode BLUE_FAINT;
    static const colorCode MAGENTA_FAINT;
    static const colorCode CYAN_FAINT;
    static const colorCode WHITE_FAINT;

    static const colorCode RESET;
    
    static void printColorTest();
};
}
