#include "InputHandler.h"
#include "Enemy.h"

#include "DumbEnemy.h"
#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Wall.h"

#include <iostream>

DumbEnemy::DumbEnemy(const sf::Vector2f& position, bool isActive)
  :Enemy(position, isActive)
{
  m_changeDirTimer = 0;
}

void DumbEnemy::update(float deltaTime, const LevelData* /*levelData*/)
{
  if (!isActive())
    return;

  updateDirTime(deltaTime);
  move(deltaTime);
  keepObjInsideMap();
  checkFallingOutsideMap();
}

void DumbEnemy::handleCollision(Object& obj)
{
  obj.handleCollision(*this);
}
void DumbEnemy::handleCollision(Player& obj)
{
  obj.handleCollision(*this);
}
void DumbEnemy::handleCollision(Enemy& /*obj*/)
{
}
void DumbEnemy::handleCollision(Coin& /*obj*/)
{
}
void DumbEnemy::handleCollision(Wall& obj)
{
  resolveOverlap(obj);
}
void DumbEnemy::handleCollision(Ground& obj)
{
  resolveOverlap(obj);
}
void DumbEnemy::handleCollision(Ladder& obj)
{
  if (isOnObject(obj))
  {
    setOnLadder(true);
    handleLadderLogic(obj);
  }
}
void DumbEnemy::handleCollision(Rope& obj)
{
  handleRopeLogic(obj);
}

sf::Vector2f DumbEnemy::getDirection()
{
  if (m_changeDirTimer <= 0)
  {
    auto dir = mapAction(InputHandler::getRandomMovementInput());

    m_currentDir = static_cast<sf::Vector2f>(dir);
    // זמן רנדומלי בין 1 ל-3 שניות
    m_changeDirTimer = (std::rand() % 200 + 100) / 100.0f;
  }

  return m_currentDir;
}

void DumbEnemy::updateDirTime(float deltaTime)
{
  m_changeDirTimer -= deltaTime;
}