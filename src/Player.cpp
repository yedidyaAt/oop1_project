#include "Player.h"

Player::Player(const sf::Vector2f& position, bool isActive)
              :MovingObject(position,Symbol::PLAYER,isActive){}

void Player::update(const Level&, float deltaTime)
{
}




