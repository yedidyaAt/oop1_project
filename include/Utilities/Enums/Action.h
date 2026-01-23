#pragma once
#include <SFML/System/Vector2.hpp>

enum class Action
{
    NONE,
    DIG_LEFT_DOWN,
    DIG_RIGHT_DOWN,
    MOVE_LEFT, 
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN
};

sf::Vector2i mapAction(const Action& action);