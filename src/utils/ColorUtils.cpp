#include "ColorUtils.h"

#include <iostream>

using namespace ev3;

const ColorUtils::colorCode ColorUtils::BLACK{"\033[30m"};
const ColorUtils::colorCode ColorUtils::RED{"\033[31m"};
const ColorUtils::colorCode ColorUtils::GREEN{"\033[32m"};
const ColorUtils::colorCode ColorUtils::YELLOW{"\033[33m"};
const ColorUtils::colorCode ColorUtils::BLUE{"\033[34m"};
const ColorUtils::colorCode ColorUtils::MAGENTA{"\033[35m"};
const ColorUtils::colorCode ColorUtils::CYAN{"\033[36m"};
const ColorUtils::colorCode ColorUtils::WHITE{"\033[37m"};

const ColorUtils::colorCode ColorUtils::BLACK_BOLD{"\033[30;1m"};
const ColorUtils::colorCode ColorUtils::RED_BOLD{"\033[31;1m"};
const ColorUtils::colorCode ColorUtils::GREEN_BOLD{"\033[32;1m"};
const ColorUtils::colorCode ColorUtils::YELLOW_BOLD{"\033[33;1m"};
const ColorUtils::colorCode ColorUtils::BLUE_BOLD{"\033[34;1m"};
const ColorUtils::colorCode ColorUtils::MAGENTA_BOLD{"\033[35;1m"};
const ColorUtils::colorCode ColorUtils::CYAN_BOLD{"\033[36;1m"};
const ColorUtils::colorCode ColorUtils::WHITE_BOLD{"\033[37;1m"};

const ColorUtils::colorCode ColorUtils::BLACK_FAINT{"\033[30;2m"};
const ColorUtils::colorCode ColorUtils::RED_FAINT{"\033[31;2m"};
const ColorUtils::colorCode ColorUtils::GREEN_FAINT{"\033[32;2m"};
const ColorUtils::colorCode ColorUtils::YELLOW_FAINT{"\033[33;2m"};
const ColorUtils::colorCode ColorUtils::BLUE_FAINT{"\033[34;2m"};
const ColorUtils::colorCode ColorUtils::MAGENTA_FAINT{"\033[35;2m"};
const ColorUtils::colorCode ColorUtils::CYAN_FAINT{"\033[36;2m"};
const ColorUtils::colorCode ColorUtils::WHITE_FAINT{"\033[37;2m"};

const ColorUtils::colorCode ColorUtils::RESET{"\033[39;0m"};

void ColorUtils::printColorTest()
{
    std::cout << BLACK << "TEST " << RESET;
    std::cout << RED << "TEST " << RESET;
    std::cout << GREEN << "TEST " << RESET;
    std::cout << YELLOW << "TEST " << RESET;
    std::cout << BLUE << "TEST " << RESET;
    std::cout << MAGENTA << "TEST " << RESET;
    std::cout << CYAN << "TEST " << RESET;
    std::cout << WHITE << "TEST " << RESET << "\n";
    std::cout << BLACK_BOLD << "TEST " << RESET;
    std::cout << RED_BOLD << "TEST " << RESET;
    std::cout << GREEN_BOLD << "TEST " << RESET;
    std::cout << YELLOW_BOLD << "TEST " << RESET;
    std::cout << BLUE_BOLD << "TEST " << RESET;
    std::cout << MAGENTA_BOLD << "TEST " << RESET;
    std::cout << CYAN_BOLD << "TEST " << RESET;
    std::cout << WHITE_BOLD << "TEST " << RESET << "\n";
    std::cout << BLACK_FAINT << "TEST " << RESET;
    std::cout << RED_FAINT << "TEST " << RESET;
    std::cout << GREEN_FAINT << "TEST " << RESET;
    std::cout << YELLOW_FAINT << "TEST " << RESET;
    std::cout << BLUE_FAINT << "TEST " << RESET;
    std::cout << MAGENTA_FAINT << "TEST " << RESET;
    std::cout << CYAN_FAINT << "TEST " << RESET;
    std::cout << WHITE_FAINT << "TEST " << RESET << "\n";
}
