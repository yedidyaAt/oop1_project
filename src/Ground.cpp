#include "StaticObject.h"

#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rope.h"

Ground::Ground(const sf::Vector2f& position, bool isActive)
  :StaticObject(position, ObjectSymbol::GROUND,isActive)
{
}


void Ground::handleCollision(Object& obj) 
{
//igonr
}
void Ground::handleCollision(Player & obj) 
{
  obj.handleCollision(*this);
}
void Ground::handleCollision(Enemy & obj) 
{

}
void Ground::handleCollision(Coin & obj) 
{

}
void Ground::handleCollision(Wall & obj)
{
//ignor
}
void Ground::handleCollision(Ground & obj) 
{
//ignor
}
void Ground::handleCollision(Ladder & obj) 
{
//ignor
}
void Ground::handleCollision(Rope & obj) 
{
  //ignor
}
