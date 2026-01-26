#include "StaticObject.h"

#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

#include "Factory.h"
#include "LevelData.h"

static const bool registered = Factory::instance().registerType(ObjectSymbol::ROPE,
  [](const sf::Vector2f& pos, const LevelData& /*data*/)
  {
    return std::make_unique<Rope>(pos);
  }
);

Rope::Rope(const sf::Vector2f& position, bool isActive)
  :StaticObject(position, ObjectSymbol::ROPE, isActive)
{
}

void Rope::handleCollision(Object& /*obj*/)
{
}
void Rope::handleCollision(Player& obj)
{
  obj.handleCollision(*this);
}
void Rope::handleCollision(Enemy& obj)
{
  obj.handleCollision(*this);
}
void Rope::handleCollision(Coin& /*obj*/)
{
}
void Rope::handleCollision(Wall& /*obj*/)
{
}
void Rope::handleCollision(Ground& /*obj*/)
{
}
void Rope::handleCollision(Ladder& /*obj*/)
{
}
void Rope::handleCollision(Rope& /*obj*/)
{
}