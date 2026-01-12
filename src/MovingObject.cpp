#include "MovingObject.h"

MovingObject::MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive)
  :Object(position, symbol, isActive)
{
}

Layer MovingObject::getLayer()
{
    return Layer::DYNAMICS;
}

sf::Vector2f MovingObject::getVelocity(const sf::Vector2f& dir, float speed, float deltaTime) const
{
  return dir*speed*deltaTime;
}


