#include "StaticObject.h"

#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Rope.h"
#include "Factory.h"

static bool registered = Factory::instance().registerType(ObjectSymbol::LADDER,
  [](const sf::Vector2f& pos, const LevelData& data)
  {
    return std::make_unique<Ladder>(pos);
  }
);


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
  obj.handleCollision(*this);
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