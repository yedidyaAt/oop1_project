#include "StaticObject.h"

#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

Rope::Rope(const sf::Vector2f& position, bool isActive)
  :StaticObject(position, ObjectSymbol::ROPE, isActive)
{
}


void Rope::handleCollision(Object& obj) 
{
//igonr
}
void Rope::handleCollision(Player & obj) 
{
  obj.handleCollision(*this);
}
void Rope::handleCollision(Enemy & obj) 
{

}
void Rope::handleCollision(Coin & obj) 
{

}
void Rope::handleCollision(Wall & obj)
{
//ignor
}
void Rope::handleCollision(Ground & obj) 
{
//ignor
}
void Rope::handleCollision(Ladder & obj) 
{
//ignor
}
void Rope::handleCollision(Rope & obj) 
{  
  //ignor
}