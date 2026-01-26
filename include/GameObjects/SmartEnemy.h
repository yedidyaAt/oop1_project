#pragma once

#include "Enemy.h"

class SmartEnemy : public Enemy
{ 
public:
	explicit SmartEnemy(const sf::Vector2f& position, bool isActive = true);

	void update(float deltaTime, const LevelData* levelData) override;

  void handleCollision(Object& obj)  override;
  void handleCollision(Player& obj)  override;
  void handleCollision(Enemy& obj)   override;
  void handleCollision(Coin& obj)    override;
  void handleCollision(Wall& obj)    override;
  void handleCollision(Ground& obj)  override;
  void handleCollision(Ladder& obj)  override;
  void handleCollision(Rope& obj)    override;

  sf::Vector2f getDirection()override ;
private:
  sf::Vector2f getHafeSmartDir()const;
  sf::Vector2f getSmartNextDir(const sf::Vector2f& start,const sf::Vector2f& target)const;
};

