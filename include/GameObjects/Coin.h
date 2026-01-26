#pragma once

#include"StaticObject.h"

class Coin: public StaticObject
{
public:
  explicit Coin(const sf::Vector2f& position,int value = 0,bool isActive = true);

  void handleCollision(Object& obj)  override;
  void handleCollision(Player& obj)  override;
  void handleCollision(Enemy& obj)   override;
  void handleCollision(Coin& obj)    override;
  void handleCollision(Wall& obj)    override;
  void handleCollision(Ground& obj)  override;
  void handleCollision(Ladder& obj)  override;
  void handleCollision(Rope& obj)    override;

  int getValue()const;
private:
  int m_value;
};