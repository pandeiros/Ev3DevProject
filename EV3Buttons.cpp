#include "EV3Buttons.h"

unsigned int EV3Buttons::getButtonCode()
{
    unsigned int code = 0;

    code += ev3dev::button::back.pressed() * BACK;
    code += ev3dev::button::left.pressed() * LEFT;
    code += ev3dev::button::right.pressed() * RIGHT;
    code += ev3dev::button::up.pressed() * UP;
    code += ev3dev::button::down.pressed() * DOWN;
    code += ev3dev::button::enter.pressed() * ENTER;

    return code;
}
