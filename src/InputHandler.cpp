#include "InputHandler.h"

sf::Vector2f InputHandler::getMovementInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right))
    return sf::Vector2f(1, 0);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left))
    return sf::Vector2f(-1, 0);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up))
    return sf::Vector2f(0, -1);
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down))
    return sf::Vector2f(0, 1);

  return sf::Vector2f(0, 0);
}

Action InputHandler::getActionInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z))
    return Action::DIG_LEFT;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X))
    return Action::DIG_RIGHT;

  return Action::NONE;
}

sf::Vector2f InputHandler::getRandomInput()
{
  sf::Vector2f arr[4] = { {-1,0},{1,0},{0,-1},{0,1} };
  auto geussing = std::rand() % 4;
  return arr[geussing];
}
