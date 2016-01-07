#include "Behaviour.h"

using namespace ev3;

Behaviour::Behaviour() { }

Behaviour::Behaviour(ActionsVector actions)
: _actions(actions) { };

Behaviour::~Behaviour() { };