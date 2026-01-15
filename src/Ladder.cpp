#include "StaticObject.h"

#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Rope.h"

Ladder::Ladder(const sf::Vector2f& position, bool isActive)
  :StaticObject(position,ObjectSymbol::LADDER,isActive)
{
}

void Ladder::handleCollision(Object& obj) 
{
//igonr
}
void Ladder::handleCollision(Player & obj) 
{
  obj.handleCollision(*this);
}
void Ladder::handleCollision(Enemy & obj) 
{

}
void Ladder::handleCollision(Coin & obj) 
{

}
void Ladder::handleCollision(Wall & obj)
{
//ignor
}
void Ladder::handleCollision(Ground & obj) 
{
//ignor
}
void Ladder::handleCollision(Ladder & obj) 
{
//ignor
}
void Ladder::handleCollision(Rope & obj) 
{  
  //ignor
}