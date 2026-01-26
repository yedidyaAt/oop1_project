#pragma once

#include "MovingObject.h"

class Enemy :public MovingObject
{
public:
  explicit Enemy(const sf::Vector2f& position, bool isActive = true);

     void update(float deltaTime, const LevelData* levelData) override = 0;

     void handleCollision(Object& obj) override = 0;
     void handleCollision(Player& obj) override = 0;
     void handleCollision(Enemy& obj) override = 0;
     void handleCollision(Coin& obj) override = 0;
     void handleCollision(Wall& obj) override = 0;
     void handleCollision(Ground& obj) override = 0;
     void handleCollision(Ladder& obj) override = 0;
     void handleCollision(Rope& obj) override = 0;

     sf::Vector2f getDirection()override = 0;

private:
};