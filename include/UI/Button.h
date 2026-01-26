#pragma once
#include <SFML/Graphics.hpp>
#include "ButtonType.h"
#include "WindowManager.h"

class Button
{
public:
  explicit Button(const sf::Font& font, ButtonType type = ButtonType::NONE);

  void draw(WindowManager& window)const;

  void handlHover(const sf::Vector2f& hoverPos);
  ButtonType handlClick(const sf::Vector2f& clickPos);

  sf::FloatRect getLocalBounds()const;
  sf::FloatRect getGlobalBounds()const;
  void setScale(const sf::Vector2f& s);

  void setButtonType(ButtonType type);
  void setPos(float x, float y);
  
  void setSizeAndOrigin(float fontSize);
private:
  bool isContain(const sf::Vector2f& pos);
  void setButtonTextByType(ButtonType type);
  //void setBg();

  sf::Text m_text;
  sf::RectangleShape m_background;
  ButtonType m_type;
  bool m_isHover = false;
};