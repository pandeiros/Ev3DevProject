#include "Command.h"

using namespace ev3;

Command::Command() : _debugInfo("Main command") { }

void Command::execute() { }

std::string Command::getString()
{
    return _debugInfo;
}



