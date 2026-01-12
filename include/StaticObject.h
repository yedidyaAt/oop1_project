#pragma once
#include "Object.h"

class Level;
class StaticObject: public Object
{
public:
  StaticObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive = true);

  void update(const Level& world, float deltaTime)override;
private:

};