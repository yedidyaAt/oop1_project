#pragma once
#include "Enemy.h"


class DumbEnemy: public Enemy
{
public:
	explicit DumbEnemy(const sf::Vector2f& position, bool isActive = true);
	
	void update(float deltaTime, const LevelData* levelData) override;

  void handleCollision(Object& obj)  override;
  void handleCollision(Player& obj)  override;
  void handleCollision(Enemy& obj)   override;
  void handleCollision(Coin& obj)    override;
  void handleCollision(Wall& obj)    override;
  void handleCollision(Ground& obj)  override;
  void handleCollision(Ladder& obj)  override;
  void handleCollision(Rope& obj)    override;

  sf::Vector2f getDirection() override ;

private:
  void updateDirTime(float deltaTime);

  float m_changeDirTimer;
  sf::Vector2f m_currentDir;
};

