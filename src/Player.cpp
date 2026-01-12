#include "Player.h"
#include "InputHandler.h"
#include "Level.h"
#include <iostream>

Player::Player(const sf::Vector2f& position, bool isActive)
              :MovingObject(position,ObjectSymbol::PLAYER,isActive){}

void Player::update(const Level& level, float deltaTime)
{
  move(level, deltaTime);
}

void Player::move(const Level& level, float deltaTime)
{
  if (deltaTime > 0.05f) deltaTime = 0.05f;
  sf::Vector2f dir = InputHandler::getMovementInput();
  sf::Vector2f velocity = getVelocity(dir, GameConfig::Physics::SPEED, deltaTime);

  sf::Vector2f nextPos = level.getMoveTo(getBoundRec(), velocity,deltaTime);

  setPos(nextPos);
}




