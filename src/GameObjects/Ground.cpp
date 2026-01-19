#include "StaticObject.h"

#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ladder.h"
#include "Rope.h"
#include "Factory.h"

static bool registered = Factory::instance().registerType(ObjectSymbol::GROUND,
  [](const sf::Vector2f& pos, const LevelData& data)
  {
    return std::make_unique<Ground>(pos);
  }
);


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
  obj.handleCollision(*this);
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
}
void Ground::handleCollision(Ladder & obj) 
{
//ignor
}
void Ground::handleCollision(Rope & obj) 
{
  //ignor
}
