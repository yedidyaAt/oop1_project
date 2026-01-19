#pragma once

#include "MovingObject.h"

class Enemy :public MovingObject
{
public:
  Enemy(const sf::Vector2f& position, bool isActive = true);

     virtual void update(float deltaTime) override = 0;

    virtual void handleCollision(Object& obj) override = 0;
    virtual void handleCollision(Player& obj) override = 0;
    virtual void handleCollision(Enemy& obj) override = 0;
    virtual void handleCollision(Coin& obj) override = 0;
    virtual void handleCollision(Wall& obj) override = 0;
    virtual void handleCollision(Ground& obj) override = 0;
    virtual void handleCollision(Ladder& obj) override = 0;
    virtual void handleCollision(Rope& obj) override = 0;

    virtual sf::Vector2f getDirection()override = 0;

private:
};