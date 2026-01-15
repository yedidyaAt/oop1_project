
#include "Enemy.h"

#include "DumbEnemy.h"
#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Wall.h"

DumbEnemy::DumbEnemy(const sf::Vector2f& position, bool isActive)
                    :Enemy(position,isActive){}

void DumbEnemy::update(float deltaTime)
{
}

void DumbEnemy::handleCollision(Object& obj) 
{
//igonr
}
void DumbEnemy::handleCollision(Player & obj) 
{
}
void DumbEnemy::handleCollision(Enemy & obj) 
{
}
void DumbEnemy::handleCollision(Coin & obj) 
{
}
void DumbEnemy::handleCollision(Wall & obj)
{
//ignor
}
void DumbEnemy::handleCollision(Ground & obj) 
{
//ignor
}
void DumbEnemy::handleCollision(Ladder & obj) 
{
//ignor
}
void DumbEnemy::handleCollision(Rope & obj) 
{
  //ignor
}

sf::Vector2f DumbEnemy::getDirection()
{
    return sf::Vector2f();
}

