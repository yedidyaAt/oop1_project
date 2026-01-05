#pragma once
#include "Enemy.h"

class DumbEnemy: public Enemy
{
public:
	DumbEnemy(const sf::Vector2f& position, bool isActive = true);
	
	void update(const Level&, float deltaTime) override;
};

