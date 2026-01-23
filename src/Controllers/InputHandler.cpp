#include "InputHandler.h"

Action InputHandler::getMovementInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    return Action::MOVE_RIGHT;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    return Action::MOVE_LEFT;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    return Action::MOVE_UP;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    return Action::MOVE_DOWN;

  return Action::NONE;
}

Action InputHandler::getDigInput()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Z))
    return Action::DIG_LEFT_DOWN;
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::X))
    return Action::DIG_RIGHT_DOWN;

  return Action::NONE;
}

Action InputHandler::getRandomMovementInput()
{
  Action move[4] = { Action::MOVE_DOWN,Action::MOVE_UP,Action::MOVE_LEFT,Action::MOVE_RIGHT};
  auto geussing = std::rand() % 4;
  return move[geussing];
}
