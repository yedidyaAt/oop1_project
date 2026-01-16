#pragma once
#include <SFML/System/Vector2.hpp>


#include "MovingObject.h"

struct PlayerPackage
{
  int m_life     = 0 ;
  int m_score    = 0 ;
  int m_coinLeft = 0;
  int m_curLevel = 0;
};

class Player : public MovingObject {
public:
  Player(const sf::Vector2f& position,const PlayerPackage& package ,bool isActive = true);

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
  
  void setCoinCreated(int cnt);
  void lifeLost();
protected:
  void takeCoin(int value);

private:
  void addScore(int value);
  void addScroeCommplete();
  PlayerPackage m_package;
};
