#include "Resources.h"
#include "Object.h"
#include <iostream>

Object::Object(const sf::Vector2f& pos, ObjectSymbol symbol, bool isActive)
      :m_sprite(Resources::instance().getObjectTexture(ObjectSymbol::EMPTY))
      ,m_startPos(pos), m_symbol(symbol), m_isActive(isActive)
       {
        setSprite(pos);
       }


Layer Object::getLayer()
{
    return Layer::STATIC;
}

sf::Vector2f Object::getPos() const
{
  return m_sprite.getPosition(); 
}

void Object::setPos(const sf::Vector2f& newPos)
{
  m_sprite.setPosition(newPos);
}

void Object::setSprite(const sf::Vector2f& pos)
{
  m_sprite.setPosition(pos);
  m_sprite.setTexture(Resources::instance().getObjectTexture(m_symbol));
}

void Object::setScaleSprite()
{
  sf::Vector2u texS = m_sprite.getTexture().getSize();

  // --- הדפסת דיבאג ---
  std::cout << "Tile Size: " << UiConfig::TILE_SIZE
    << " | Texture Size: " << texS.x << "x" << texS.y << std::endl;

  float scaleX = UiConfig::TILE_SIZE / (float)texS.x;
  float scaleY = UiConfig::TILE_SIZE / (float)texS.y;

  //float scale = std::min(scaleX, scaleY);

  m_sprite.setScale({ scaleX,scaleY });
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
  if (this == &other)
    return false;

  if (other.isActive())
    return getBoundRec().findIntersection(other.getBoundRec()).has_value();
  else
    return false;
}

void Object::destroy()
{
  m_isActive = false;
}

void Object::resetStartPos()
{
  setPos(m_startPos);
}

void Object::draw(sf::RenderWindow& window)const 
{
  if(isActive())
    window.draw(m_sprite);
}
