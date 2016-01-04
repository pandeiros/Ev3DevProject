#include "ColorUtils.h"

const ColorUtils::colorCode ColorUtils::RED
{
    "\033[31m"
};
const ColorUtils::colorCode ColorUtils::GREEN{"\033[32m"};
const ColorUtils::colorCode ColorUtils::YELLOW{"\033[33m"};
const ColorUtils::colorCode ColorUtils::BLUE{"\033[34m"};

const ColorUtils::colorCode ColorUtils::RED_BOLD{"\033[31;1m"};
const ColorUtils::colorCode ColorUtils::GREEN_BOLD{"\033[32;1m"};
const ColorUtils::colorCode ColorUtils::YELLOW_BOLD{"\033[33;1m"};
const ColorUtils::colorCode ColorUtils::BLUE_BOLD{"\033[34;1m"};

const ColorUtils::colorCode ColorUtils::RED_FAINT{"\033[31;2m"};
const ColorUtils::colorCode ColorUtils::GREEN_FAINT{"\033[32;2m"};
const ColorUtils::colorCode ColorUtils::YELLOW_FAINT{"\033[33;2m"};
const ColorUtils::colorCode ColorUtils::BLUE_FAINT{"\033[34;2m"};

const ColorUtils::colorCode ColorUtils::RESET{"\033[39;0m"};
