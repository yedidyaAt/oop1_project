#include "MovingObject.h"

#include "InputHandler.h"
#include <iostream>

#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Enemy.h"
#include "Wall.h"

#include "Factory.h"
#include "LevelData.h"
#include "SoundType.h"
#include "UiConfig.h"

static const bool registered = Factory::instance().registerType(ObjectSymbol::PLAYER,
  [](const sf::Vector2f& pos, const LevelData& data) 
  {
    PlayerPackage package;
    package.m_coinLeft = data.m_coinLeft; // <- 0 //for initialstion
    package.m_life = data.m_life;
    package.m_score = data.m_score;
    package.m_curLevel = data.m_curLevel;

    return std::make_unique<Player>(pos,package);
  }
);

Player::Player(const sf::Vector2f& position, const PlayerPackage& package, bool isActive)
              :MovingObject(position,ObjectSymbol::PLAYER,isActive)
{
  m_package = package;
  m_deadReason = DeathReason::NONE;
}

void Player::update(float deltaTime,const LevelData* levelData)
{
  if (!isActive())
    return;

  move(deltaTime);
  digGround();
  keepObjInsideMap();
  handlFallingOutside();
  checkTimerUp(levelData);
}


sf::Vector2f Player::getDirection()
{
  auto dir = mapAction(InputHandler::getMovementInput());
  return static_cast<sf::Vector2f>(dir);
}

void Player::handleCollision(Object& obj)
{
  obj.handleCollision(*this);
}

void Player::handleCollision(Player& /*obj*/)
{
}

void Player::handleCollision(Enemy& /*obj*/)
{
  playerKilled();
}

void Player::handleCollision(Coin& obj)
{
  takeCoin(obj.getValue());
}

void Player::handleCollision(Wall& obj)
{
  resolveOverlap(obj);
}

void Player::handleCollision(Ground& obj)
{
  resolveOverlap(obj);
}

void Player::handleCollision(Ladder& obj)
{
  if (isOnObject(obj))
  {
    setOnLadder(true);
    handleLadderLogic(obj);
  }
}

void Player::handleCollision(Rope& obj)
{
  handleRopeLogic(obj);
}

void Player::setCoinCreated(int cnt)
{
  m_package.m_coinLeft = cnt;
}

void Player::checkTimerUp(const LevelData* levelData)
{
  if (levelData->m_timer <= 0)
    timesUp();
}

void Player::playerKilled()
{
  lifeLost();
  m_deadReason = DeathReason::KILLED;
}

void Player::timesUp()
{
  lifeLost();
  m_deadReason = DeathReason::TIMES_UP;
}

void Player::reset()
{
  MovingObject::reset();
  m_deadReason = DeathReason::NONE;
}

void Player::lifeLost()
{ 
  SoundManager::instance().playSound(SoundType::LIFE_LOST);
  sf::sleep(sf::seconds(2));
  destroy();
  m_package.m_life--;

}

const PlayerPackage& Player::getPackage() const
{
  return m_package;
}

DeathReason Player::getDeathReason() const
{
    return m_deadReason;
}

void Player::takeCoin(int value)
{
  m_package.m_coinLeft--;
  addScore(value);
  addScroeCommplete();
}

void Player::digGround()
{
  const sf::Vector2f digPos = getDigPos();

  if (getBoard())
    getBoard()->tryToDig(digPos);
}

void Player::handlFallingOutside()
{
  if (checkFallingOutsideMap())
    playerKilled();
}

sf::Vector2f Player::ActionToPos(Action action) const
{
  if (action == Action::NONE)
    return { -1.f,-1.f };
  
  const sf::Vector2f curCenterPos = getBoundRec().getCenter();
  const float tileSize = UiConfig::TILE_SIZE;
  sf::Vector2f digPos = { 0, curCenterPos.y + tileSize };

  if (action == Action::DIG_LEFT_DOWN)
  {
    digPos.x = curCenterPos.x - tileSize;
  }
  else if (action == Action::DIG_RIGHT_DOWN)
  {
    digPos.x = curCenterPos.x + tileSize;
  }

  return digPos;
}

sf::Vector2f Player::getDigPos() const
{
  Action action = InputHandler::getDigInput();
  return ActionToPos(action);
}

void Player::addScore(int value)
{
  m_package.m_score += value;
}

void Player::addScroeCommplete()
{
  if (!m_package.m_coinLeft)
  {
    int score = m_package.m_curLevel * GameRules::LEVEL_COMPLETE_BONUS;
    addScore(score);
  }
}


