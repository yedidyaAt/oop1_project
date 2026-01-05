#pragma once
#include "Enemy.h"

class SmartEnemy : public Enemy
{
public:
	SmartEnemy(const sf::Vector2f& position, bool isActive = true);

	void update(const Level&, float deltaTime) override;

private:
};

