#pragma once

#include "StaticObject.h"

class Ground : public StaticObject
{
public:
  Ground(const sf::Vector2f& position, bool isActive = true);

  void handleCollision(Object& obj)  override;
  void handleCollision(Player& obj)  override;
  void handleCollision(Enemy& obj)   override;
  void handleCollision(Coin& obj)    override;
  void handleCollision(Wall& obj)    override;
  void handleCollision(Ground& obj)  override;
  void handleCollision(Ladder& obj)  override;
  void handleCollision(Rope& obj)    override;

private:
};