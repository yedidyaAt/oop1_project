#pragma once
#include "MovingObject.h"

class Enemy :public MovingObject
{
public:
  Enemy(const sf::Vector2f& position, bool isActive = true);

  virtual void update(const Level& world, float deltaTime) override = 0;
private:
};