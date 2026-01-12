#include "Object.h"
#include <iostream>

Object::Object(const sf::Vector2f& pos, ObjectSymbol symbol, bool isActive)
      :m_pos(pos),m_startPos(pos), m_symbol(symbol), m_isActive(isActive){}


Layer Object::getLayer()
{
    return Layer::STATIC;
}

sf::Vector2f Object::getPos() const
{
  return m_pos; 
}

void Object::setPos(const sf::Vector2f& newPos)
{
  m_pos = newPos;
}

ObjectSymbol Object::getSymbol() const
{
  return m_symbol;
}

sf::FloatRect Object::getBoundRec() const
{
  return sf::FloatRect{getPos(),{UiConfig::TILE_SIZE,UiConfig::TILE_SIZE} };
}

bool Object::isActive() const
{
  return m_isActive;
}

bool Object::haveColision(const Object& other) const
{

  if (other.isActive())
    return getBoundRec().findIntersection(other.getBoundRec()).has_value();
  else return false;
}

void Object::destroy()
{
  m_isActive = false;
}

void Object::resetStartPos()
{
  setPos(m_startPos);
}
