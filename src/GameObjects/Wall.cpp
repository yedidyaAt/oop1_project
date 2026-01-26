#include "StaticObject.h"

#include "Wall.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"

#include "Factory.h"
#include "LevelData.h"

static const bool registered = Factory::instance().registerType(ObjectSymbol::WALL,
  [](const sf::Vector2f& pos, const LevelData& /*data*/)
  {
    return std::make_unique<Wall>(pos);
  }
);


Wall::Wall(const sf::Vector2f& position, bool isActive)
  :StaticObject(position, ObjectSymbol::WALL, isActive)
{
}

void Wall::handleCollision(Object& /*obj*/)
{
}
void Wall::handleCollision(Player& obj)
{
  obj.handleCollision(*this);
}
void Wall::handleCollision(Enemy& obj)
{
  obj.handleCollision(*this);
}
void Wall::handleCollision(Coin& /*obj*/)
{
}
void Wall::handleCollision(Wall& /*obj*/)
{
}
void Wall::handleCollision(Ground& /*obj*/)
{
}
void Wall::handleCollision(Ladder& /*obj*/)
{
}
void Wall::handleCollision(Rope& /*obj*/)
{
}