#include "SignalHandler.h"

using namespace ev3;

Robot * SignalHandler::robot = nullptr;
Master * SignalHandler::master = nullptr;

void SignalHandler::HandleSignal(int signum)
{
    Logger::getInstance()->log("Signal caught: " + std::to_string(signum),
            ev3::Logger::WARNING);

    if (SignalHandler::robot)
        SignalHandler::robot->stop();
    if (SignalHandler::master)
        SignalHandler::master->stop();

    Devices::destroy();

    exit(signum);
}
