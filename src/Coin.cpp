#include "StaticObject.h"

#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ground.h"
#include "Ladder.h"
#include "Rope.h"

Coin::Coin(const sf::Vector2f& position,bool isActive)
  :StaticObject(position,ObjectSymbol::COIN,isActive)
{
}


void Coin::handleCollision(Object& obj) 
{
//igonr
}
void Coin::handleCollision(Player & obj) 
{
  destroy();
  SoundManager::instance().playSound(SoundType::COLLECT_COIN);
  obj.handleCollision(*this);
}
void Coin::handleCollision(Enemy & obj) 
{

}
void Coin::handleCollision(Coin & obj) 
{

}
void Coin::handleCollision(Wall & obj)
{
//ignor
}
void Coin::handleCollision(Ground & obj) 
{
//ignor
}
void Coin::handleCollision(Ladder & obj) 
{
//ignor
}
void Coin::handleCollision(Rope & obj) 
{
  //ignor
}
