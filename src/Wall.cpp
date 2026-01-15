#include "StaticObject.h"

#include "Wall.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"

Wall::Wall(const sf::Vector2f& position, bool isActive)
  :StaticObject(position, ObjectSymbol::WALL,isActive)
{
}

void Wall::handleCollision(Object& obj) 
{
//igonr
}
void Wall::handleCollision(Player & obj) 
{
  obj.handleCollision(*this);
}
void Wall::handleCollision(Enemy & obj) 
{

}
void Wall::handleCollision(Coin & obj) 
{

}
void Wall::handleCollision(Wall & obj)
{
//ignor
}
void Wall::handleCollision(Ground & obj) 
{
//ignor
}
void Wall::handleCollision(Ladder & obj) 
{
//ignor
}
void Wall::handleCollision(Rope & obj) 
{
  //ignor
}