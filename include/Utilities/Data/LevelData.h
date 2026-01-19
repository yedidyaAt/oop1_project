#pragma once
#include <SFML/System/Vector2.hpp>
#include "GameRules.h"

struct LevelData
{
    int m_curLevel = GameRules::START_LEVEL;
    int m_life     = GameRules::STARTING_LIVES;
    int m_score    = GameRules::START_SCORE;
    float m_timer  = GameRules::LEVEL_TIMER;

    int m_coinLeft = 0;
    sf::Vector2u m_LevelSize;
};
