#pragma once
#include <SFML/System/Vector2.hpp>


#include "MovingObject.h"

class Player : public MovingObject {
public:
  Player(const sf::Vector2f& position, bool isActive = true);

  void update(float deltaTime) override;

  sf::Vector2f getDirection() override;
  
  void handleCollision(Object & obj)  override;
  void handleCollision(Player & obj)  override;
  void handleCollision(Enemy & obj)   override;
  void handleCollision(Coin & obj)    override;
  void handleCollision(Wall & obj)    override;
  void handleCollision(Ground & obj)  override;
  void handleCollision(Ladder & obj)  override;
  void handleCollision(Rope & obj)    override;
  
protected:
  bool isCoinTaked();
  void coinTaked();
private:
  bool m_coinTaked = false;
};
