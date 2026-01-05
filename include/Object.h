#pragma once
#include <SFML/System/Vector2.hpp>
#include "Const.h"
#include "io.h"

// Forward declaration 
class Level;

class Object {
public:
  Object(const sf::Vector2f& position, Symbol symbol, bool isActive = true);
  virtual ~Object() = default;

  // Pure Virtual:
  virtual void update(const Level& world, float deltaTime) = 0;

  // (Concrete) 
  sf::Vector2f getPos() const;
  Symbol getSymbol() const;
  bool isActive() const;
  void destroy();

  //temporary
  void draw()const;

protected:
  void setPos(const sf::Vector2f& newPos);


  sf::Vector2f m_pos;
  Symbol m_symbol;
  bool m_isActive;
};