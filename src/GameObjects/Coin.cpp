#include "StaticObject.h"

#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"
#include "Ground.h"
#include "Ladder.h"
#include "Rope.h"

#include "Factory.h"
#include "LevelData.h"
#include "GameRules.h"
#include "SoundType.h"
#include <iostream>

static bool registered = Factory::instance().registerType(ObjectSymbol::COIN,
  [](const sf::Vector2f& pos, const LevelData& data)
  {
    int val = data.m_curLevel * GameRules::COIN_SCORE_VALUE;
    return std::make_unique<Coin>(pos,val);
  }
);

Coin::Coin(const sf::Vector2f& position,int value,bool isActive)
  :StaticObject(position,ObjectSymbol::COIN,isActive)
{
  m_value = value;
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

int Coin::getValue() const
{
  return m_value;
}
