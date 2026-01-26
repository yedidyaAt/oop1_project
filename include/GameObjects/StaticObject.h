#pragma once
#include "Object.h"

class StaticObject: public Object
{
public:
  StaticObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive = true);

  void update(float deltaTime, const LevelData* levelData)override;

  void handleCollision(Object& obj) override = 0;

  void reset()override;
 protected:
  void handleCollision(Player& obj) override = 0;
  void handleCollision(Enemy& obj) override = 0;
  void handleCollision(Coin& obj) override = 0;
  void handleCollision(Wall& obj) override = 0;
  void handleCollision(Ground& obj) override = 0;
  void handleCollision(Ladder& obj) override = 0;
  void handleCollision(Rope& obj) override = 0;

private:

};