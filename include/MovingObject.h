#pragma once
#include "Object.h"

class MovingObject : public Object {
public:
  MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive=true);

  virtual void update(const Level& world, float deltaTime) override = 0;
  Layer getLayer()override;
  sf::Vector2f getVelocity(const sf::Vector2f&, float speed, float deltaTime)const;
};