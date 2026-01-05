#pragma once
#include <SFML/System/Vector2.hpp>


namespace Keys
{
constexpr int ESCAPE = 27;
constexpr int SPECIAL_KEY = 224;
}

namespace SpecialKeys
{
constexpr int UP = 72;
constexpr int DOWN = 80;
constexpr int LEFT = 75;
constexpr int RIGHT = 77;
}

namespace BoardObject
{
  constexpr char PLAYER = '@';
  constexpr char ENEMY = '%';
  constexpr char WALL = '#';
  constexpr char FLOR = '#';
  constexpr char LADDER = 'H';
  constexpr char ROD = '-';
  constexpr char SPACE = ' ';
  constexpr char COIN = '*';
}


namespace Screen
{
// Reset terminal cursor location to start of the screen (0,0)
void resetLocation();
// Set terminal cursor location to the desired location
void setLocations(const sf::Vector2f& location);
}
