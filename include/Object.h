#pragma once
#include <SFML/System/Vector2.hpp>
#include "Const.h"
#include "io.h"

// Forward declaration 
class Level;

class Object {
public:
  Object(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive = true);
  virtual ~Object() = default;

  virtual void update(const Level& world, float deltaTime) = 0;

  virtual Layer getLayer();

  // (Concrete) 
  sf::Vector2f getPos() const;
  ObjectSymbol getSymbol() const;
  sf::FloatRect getBoundRec() const;
  
  bool isActive() const;
  bool haveColision(const Object& other) const;
  
  void destroy();
  void resetStartPos();


protected:
  void setPos(const sf::Vector2f& newPos);

private:
  sf::Vector2f m_pos;
  sf::Vector2f m_startPos;
  ObjectSymbol m_symbol;
  bool m_isActive;
};