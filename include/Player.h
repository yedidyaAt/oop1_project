#pragma once
#include "MovingObject.h"
#include <SFML/System/Vector2.hpp>

class Level;

class Player : public MovingObject {
public:
  Player(const sf::Vector2f& position, bool isActive = true);

  void update(const Level&, float deltaTime) override;

private:
  void move(const Level& level, float deltaTime);

};
