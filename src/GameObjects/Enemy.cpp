#include "Enemy.h"

#include "MovingObject.h"
#include "DumbEnemy.h"
#include "SmartEnemy.h"

#include "Factory.h"
#include "LevelData.h"

#include <iostream>

static bool registered = Factory::instance().registerType(
  ObjectSymbol::ENEMY,
  [](const sf::Vector2f& pos, const LevelData& data) -> std::unique_ptr<Object>
  {
    auto num = std::rand()%2;

    if (num == 0)
    {
      std::cout << "dumb was create\n";
      return std::make_unique<DumbEnemy>(pos);
    }
    else if(num == 1)
    {
      std::cout << "Smart was create\n";
      return std::make_unique<SmartEnemy>(pos);
    }
  }
);

Enemy::Enemy(const sf::Vector2f& position, bool isActive)
  :MovingObject(position, ObjectSymbol::ENEMY, isActive){}

