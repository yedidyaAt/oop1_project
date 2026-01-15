#include "MovingObject.h"

#include "InputHandler.h"
#include <iostream>
#include "Utilities.h"

#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Enemy.h"
#include "Wall.h"
#include "Factory.h"


static bool registered = Factory::instance().registerType(ObjectSymbol::PLAYER,
  [](const sf::Vector2f& pos, const LevelData& data) 
  {
    return std::make_unique<Player>(pos);
  }
);

Player::Player(const sf::Vector2f& position, bool isActive)
              :MovingObject(position,ObjectSymbol::PLAYER,isActive){}

void Player::update(float deltaTime)
{
  move(deltaTime);
}


sf::Vector2f Player::getDirection()
{
  return InputHandler::getMovementInput();
}

void Player::handleCollision(Object& obj)
{
  obj.handleCollision(*this);
}

void Player::handleCollision(Player& obj)
{
  //obj.handlCollison(*this);
}

void Player::handleCollision(Enemy& obj)
{
  //obj.handlCollison(*this);
}

void Player::handleCollision(Coin& obj)
{
  std::cout << "player take coin" << std::endl;
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
  setOnLadder(true);
  handleLadderLogic(obj);
}

void Player::handleCollision(Rope& obj)
{
  handleRopeLogic(obj);
}

bool Player::isCoinTaked()
{
  bool take = m_coinTaked;
  m_coinTaked = false;

  return take;
}

void Player::coinTaked()
{
  m_coinTaked = true;
}




