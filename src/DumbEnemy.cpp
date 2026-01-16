
#include "InputHandler.h"
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
  move(deltaTime);
}

void DumbEnemy::handleCollision(Object& obj) 
{
  obj.handleCollision(*this);
}
void DumbEnemy::handleCollision(Player & obj) 
{
  obj.handleCollision(*this);
}
void DumbEnemy::handleCollision(Enemy & obj) 
{
}
void DumbEnemy::handleCollision(Coin & obj) 
{
}
void DumbEnemy::handleCollision(Wall & obj)
{
  resolveOverlap(obj);
}
void DumbEnemy::handleCollision(Ground & obj) 
{
  resolveOverlap(obj);
}
void DumbEnemy::handleCollision(Ladder & obj) 
{
  setOnLadder(true);
  handleLadderLogic(obj);
}
void DumbEnemy::handleCollision(Rope & obj) 
{
  handleRopeLogic(obj);
}

sf::Vector2f DumbEnemy::getDirection()
{
    return InputHandler::getRandomInput();
}

