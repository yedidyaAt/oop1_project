#pragma once
#include "Object.h"

class Level;
class StaticObject: public Object
{
public:
  StaticObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive = true);

  void update(float deltaTime)override;

  virtual void handleCollision(Object& obj) override = 0;
  virtual void handleCollision(Player& obj) override = 0;
  virtual void handleCollision(Enemy& obj) override = 0;
  virtual void handleCollision(Coin& obj) override = 0;
  virtual void handleCollision(Wall& obj) override = 0;
  virtual void handleCollision(Ground& obj) override = 0;
  virtual void handleCollision(Ladder& obj) override = 0;
  virtual void handleCollision(Rope& obj) override = 0;
private:

};