#pragma once
#include <SFML/Graphics.hpp>
#include "Const.h"

class InputHandler
{
public:
  static sf::Vector2f getMovementInput();
  static Action getActionInput(); 
private:
};