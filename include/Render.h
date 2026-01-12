#pragma once
#include "Const.h"
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Level;
class Object;
class Board;
class GameBar;

class Render
{
public:
  static Render&  instance();
 
  void drawLevel(sf::RenderWindow& window, const Level& level);
  void drawBar(sf::RenderWindow& window, const GameBar& bar);

  void drawRelativeText(sf::RenderWindow& window,
    float xPrecent, float yPrecent,
    const std::string& text,
    const sf::View& curView);

private:
  Render();

 

  void setSprite(const Object& obj);
  void drawBoard(sf::RenderWindow& window, const Board& board);
  void drawObjects(sf::RenderWindow& window, const std::vector<std::unique_ptr<Object>>& objects);
  void scaleSprite(const sf::Vector2u& texSize);
 

  sf::Sprite m_sprite;
  sf::Text m_text;
};