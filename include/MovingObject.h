#pragma once
#include "Object.h"

class MovingObject : public Object {
public:
  MovingObject(const sf::Vector2f& position, Symbol symbol, bool isActive=true);

  virtual void update(const Level& world, float deltaTime) override = 0;
  
  void reset();
protected:
  sf::Vector2f m_startPos;
  float m_speed  = 1;
  sf::Vector2f m_velocity;
};