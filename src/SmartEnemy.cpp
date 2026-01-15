
#include "SmartEnemy.h"

#include "Enemy.h"
#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Wall.h"

SmartEnemy::SmartEnemy(const sf::Vector2f& position,bool isActive)
                      :Enemy(position, isActive){}


void SmartEnemy::update(float deltaTime)
{
}

void SmartEnemy::handleCollision(Object& obj)
{//igonr
}
void SmartEnemy::handleCollision(Player& obj)
{
}
void SmartEnemy::handleCollision(Enemy& obj)
{
}
void SmartEnemy::handleCollision(Coin& obj)
{
}
void SmartEnemy::handleCollision(Wall& obj)
{
//ignor
}
void SmartEnemy::handleCollision(Ground& obj)
{//ignor
}
void SmartEnemy::handleCollision(Ladder& obj)
{//ignor
}
void SmartEnemy::handleCollision(Rope& obj)
{//ignor
}

sf::Vector2f SmartEnemy::getDirection()
{
    return sf::Vector2f();
}





