#pragma once
#include <SFML/System/Vector2.hpp>
#include "Action.h"

#include "MovingObject.h"
#include "PlayerPackage.h"
#include "DeathReason.h"


class Player : public MovingObject {
public:
  Player(const sf::Vector2f& position,const PlayerPackage& package ,bool isActive = true);

  void update(float deltaTime, const LevelData* levelData) override;

  sf::Vector2f getDirection() override;
  
  void handleCollision(Object & obj)  override;
  void handleCollision(Player & obj)  override;
  void handleCollision(Enemy & obj)   override;
  void handleCollision(Coin & obj)    override;
  void handleCollision(Wall & obj)    override;
  void handleCollision(Ground & obj)  override;
  void handleCollision(Ladder & obj)  override;
  void handleCollision(Rope & obj)    override;
  
  void reset() override;
  void setCoinCreated(int cnt);
  void checkTimerUp(const LevelData* levelData);
  void playerKilled();
  void timesUp();
  void lifeLost();
  const PlayerPackage& getPackage()const;
  DeathReason getDeathReason() const;
protected:
  void takeCoin(int value);
  void digGround();
private:
  void handlFallingOutside();
  sf::Vector2f ActionToPos(Action action)const;
  sf::Vector2f getDigPos()const;
  void addScore(int value);
  void addScroeCommplete();

  PlayerPackage m_package;
  DeathReason m_deadReason;
};
