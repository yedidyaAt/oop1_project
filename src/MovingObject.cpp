#include "MovingObject.h"

MovingObject::MovingObject(const sf::Vector2f& position, Symbol symbol, bool isActive)
                          :Object(position,symbol,isActive)
{
  m_startPos = position;
}

void MovingObject::reset()
{
  setPos(m_startPos);
}

