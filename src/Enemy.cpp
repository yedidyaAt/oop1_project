#include "Enemy.h"

#include "MovingObject.h"

Enemy::Enemy(const sf::Vector2f& position, bool isActive)
  :MovingObject(position, ObjectSymbol::ENEMY, isActive){}
