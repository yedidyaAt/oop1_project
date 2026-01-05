#include "io.h"


#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef VC_EXTRALEAN
#undef WIN32_LEAN_AND_MEAN

namespace
{
  COORD locToCoord(const sf::Vector2f& loc)
  {
    auto res = COORD{};
    res.Y = static_cast<short>(loc.y);
    res.X = static_cast<short>(loc.x);
    return res;
  }
}

void Screen::resetLocation()
{
    setLocations(sf::Vector2f(0, 0));
}

void Screen::setLocations(const sf::Vector2f& location)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), locToCoord(location));
}
