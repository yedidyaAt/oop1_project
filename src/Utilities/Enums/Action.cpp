#include "Action.h"

sf::Vector2i mapAction(const Action& action)
{
  switch (action)
  {
  case Action::MOVE_LEFT:  return { -1, 0 };
  case Action::MOVE_RIGHT: return { 1, 0 };
  case Action::MOVE_UP:    return { 0, -1 };
  case Action::MOVE_DOWN:  return { 0, 1 };

  case Action::DIG_LEFT_DOWN:   return { -1, 1 };
  case Action::DIG_RIGHT_DOWN:  return { 1, 1 };

  default: return { 0, 0 };
  }
}