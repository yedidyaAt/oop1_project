#include "Object.h"
#include <iostream>

Object::Object(const sf::Vector2f& position, Symbol symbol, bool isActive)
              :m_pos(position), m_symbol(symbol), m_isActive(isActive){}


sf::Vector2f Object::getPos() const
{
  return m_pos; 
}

void Object::setPos(const sf::Vector2f& newPos)
{
  m_pos = newPos;
}

Symbol Object::getSymbol() const
{
  return m_symbol;
}

bool Object::isActive() const
{
  return m_isActive;
}

void Object::destroy()
{
  m_isActive = false;
}

void Object::draw() const
{
  Screen::setLocations(getPos());
  std::cout << static_cast<char>(m_symbol);
}
