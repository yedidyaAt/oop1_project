#include "DumbEnemy.h"

DumbEnemy::DumbEnemy(const sf::Vector2f& position, bool isActive)
                    :Enemy(position,isActive){}

void DumbEnemy::update(const Level&, float deltaTime)
{
}


