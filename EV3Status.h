#pragma once

#include "ev3dev.h"
#include <vector>
#include "EV3Config.h"
#include <string>

class EV3Status
{
public:
    EV3Status();
    EV3Status(const EV3Status& orig);
    virtual ~EV3Status();

    void run(EV3Config * config);

private:
    static const unsigned int LINE_LENGTH = 96;

    enum ALIGN
    {
        LEFT,
        RIGHT,
        CENTER
    };

    std::string getPortStatus(EV3Config * config);

    std::string printLine(std::string character);
    std::string printWithAlign(std::string begin, std::string output, std::string end, ALIGN align);
};
