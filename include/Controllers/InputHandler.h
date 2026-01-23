#pragma once
#include <SFML/Graphics.hpp>
#include "Action.h"

class InputHandler
{
public:
  static Action getMovementInput();
  static Action getDigInput(); 
  static Action getRandomMovementInput();
private:
};