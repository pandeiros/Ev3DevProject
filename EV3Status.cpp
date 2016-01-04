#include "EV3Status.h"
#include "EV3Buttons.h"
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <c++/4.9/bits/basic_string.h>

EV3Status::EV3Status() { }

EV3Status::EV3Status(const EV3Status& orig) { }

EV3Status::~EV3Status() { }

void EV3Status::run(EV3Config * config)
{
    std::vector<ev3dev::motor> motors = config->getMotors();
    std::vector<ev3dev::sensor> sensors = config->getSensors();
    std::stringstream out;

    while (1)
    {
        out.str("");

        out << "\033[2J\033[100A\033[200D";
        out << "/" << printLine("=") << "\\\n"
                << printWithAlign("|", ">>> DEVICE STATUS <<<", "|", EV3Status::CENTER);

        out << "|" << printLine("=") << "|\n"
                << printWithAlign("|", "Buttons code: " + std::to_string(EV3Buttons::getButtonCode()), "|", EV3Status::LEFT);

        out << "|" << printLine("=--=") << "|\n"
                << printWithAlign("|", "--- MOTORS --- ", "|", EV3Status::CENTER)
                << "|" << printLine("-") << "|\n";

        for (auto & m : motors)
        {
            out << printWithAlign("|", "Port: " + m.port_name(), "|", LEFT)
                    << printWithAlign("|", "Position: " + std::to_string(m.position()), "|", LEFT)
                    << printWithAlign("|", "Speed: " + std::to_string(m.speed()), "|", LEFT);


            //            out << "| Commands: ";
            //            for (auto & command : m.commands())
            //                out << command << ", ";
            //            out << "\n";
            //            
            //            out << "| State: ";
            //            for (auto & state : m.state())
            //                out << state << ", ";
            //            out << "\n";
            //            
            //            out << "| Stop commands: ";
            //            for (auto & state : m.stop_commands())
            //                out << state << ", ";
            //            out << "\n";

            //            out << "| Count per rot.: " << m.count_per_rot() << "\n";
            //            out << "| Duty cycle: " << m.duty_cycle() << "\n";
            //            out << "| Polarity: " << m.polarity() << "\n";
            //            out << "| Position: " << m.position() << "\n";
            //            out << "| Speed: " << m.speed() << "\n";
            //            out << "| Speed regulation: " << m.speed_regulation_enabled() << "\n";
            //            out << "| Stop command: " << m.stop_command() << "\n";
            out << "|" << printLine("><") << "|\n";
        }

        out << "|" << printLine("=--=") << "|\n"
                << printWithAlign("|", "--- SENSORS ---", "|", EV3Status::CENTER)
                << "|" << printLine("-") << "|\n";

        for (auto & s : sensors)
        {
            out << printWithAlign("|", "Port: " + s.port_name(), "|", LEFT)
                    << printWithAlign("|", "Value: " + std::to_string(s.value()), "|", LEFT);

            out << "|" << printLine("><") << "|\n";
        }

        out << "\\" << printLine("=") << "/\n";

        std::cout << out.str();

        usleep(100000);
    }
}

std::string EV3Status::getPortStatus(EV3Config * config)
{
    std::string status = "";

    for (int i = 0; i < INPUTS.size(); ++i)
    {
        //if (config->)
        // PRZENIESC CALY EV3CONFIG DO EV3STATUS BO SIE ROBI BURDEL!

    }

    for (int i = 0; i < OUTPUTS.size(); ++i)
    {

    }
}

std::string EV3Status::printLine(std::string character)
{
    std::string out = "";
    for (unsigned int i = 0; i < EV3Status::LINE_LENGTH / character.size(); ++i)
    {
        out += character;
    }

    return out;
}

std::string EV3Status::printWithAlign(std::string begin, std::string output, std::string end, ALIGN align)
{
    std::stringstream out;
    out << begin;
    switch (align)
    {
        case LEFT:
            out << std::setw(EV3Status::LINE_LENGTH) << std::left << " " + output;
            break;
        case RIGHT:
            out << std::setw(EV3Status::LINE_LENGTH) << std::right << " " + output;
            break;
        case CENTER:
            out << std::setw(EV3Status::LINE_LENGTH / 2 + output.size() / 2) << std::right << " " + output;
            break;
        default:
            out << std::setw(EV3Status::LINE_LENGTH) << std::left << " " + output;
    };

    if (align == CENTER)
        out << std::setw(EV3Status::LINE_LENGTH / 2 - output.size() / 2 + 1);
    out << end << "\n";
    return out.str();
}
