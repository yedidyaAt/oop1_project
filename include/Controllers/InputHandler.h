#pragma once
#include <SFML/Graphics.hpp>
#include "Action.h"

class InputHandler
{
public:
  static sf::Vector2f getMovementInput();
  static Action getActionInput(); 
  static sf::Vector2f getRandomInput();
private:
};