#pragma once
#include <SFML/Graphics.hpp>
#include "Const.h"

class Player;
class Enemy;
class Coin;
class Wall;
class Ground;
class Ladder;
class Rope;


class Object {
public:
  Object(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive = true);
  virtual ~Object() = default; 

  virtual void update(float deltaTime) = 0;

 
  virtual void handleCollision(Object& obj) =0;
  virtual void handleCollision(Player& obj) =0;
  virtual void handleCollision(Enemy& obj) =0;
  virtual void handleCollision(Coin& obj) =0;
  virtual void handleCollision(Wall& obj) =0;
  virtual void handleCollision(Ground& obj) =0;
  virtual void handleCollision(Ladder& obj) =0;
  virtual void handleCollision(Rope& obj) =0;

  virtual void reset() = 0;

  virtual Layer getLayer();

  sf::Vector2f getPos() const;
  ObjectSymbol getSymbol() const;
  sf::FloatRect getBoundRec() const;
  
  bool isActive() const;
  bool haveColision(const Object& other) const;
  
  void destroy();
  void livenUp();

  void draw(sf::RenderWindow& window)const;
  void setPos(const sf::Vector2f& newPos);

protected: 

  void resetStartPos();
private:
  void setSprite(const sf::Vector2f& pos);
  void setScaleSprite();


  sf::Sprite m_sprite;
  sf::Vector2f m_startPos;
  ObjectSymbol m_symbol;
  bool m_isActive;
};