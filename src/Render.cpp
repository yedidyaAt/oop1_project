#include "Render.h"
#include "Resources.h"
#include "Level.h"
#include "Object.h"
#include "Board.h"
#include <string>

Render& Render::instance()
{
  static Render ins;
  return ins;
}

Render::Render():
 m_sprite(Resources::instance().getObjectTexture(ObjectSymbol::EMPTY))
,m_text(Resources::instance().getFont(FontType::Damned))
{}

void Render::drawLevel(sf::RenderWindow& window, const Level& level)
{
  drawBoard(window, level.getBoard());
  drawObjects(window, level.getObject());
}

void Render::drawBar(sf::RenderWindow& window, const GameBar& bar)
{
}

void Render::setSprite(const Object& obj)
{
  ObjectSymbol symbol = obj.getSymbol();
  sf::Vector2f pos = obj.getPos();
  //pos *= UiConfig::TILE_SIZE;
  const sf::Texture& tex = Resources::instance().getObjectTexture(symbol);

  m_sprite.setTexture(tex);
  m_sprite.setPosition(pos);
}

void Render::drawBoard(sf::RenderWindow& window, const Board& board)
{
  const auto& boardObjects = board.getBoardObjects();

  for (const auto& objects : boardObjects)
    drawObjects(window, objects);
}

void Render::drawObjects(sf::RenderWindow& window, const std::vector<std::unique_ptr<Object>>& objects)
{
  for (const auto& obj : objects)
  {
    if (obj->isActive())
    {
      setSprite((*obj));
      window.draw(m_sprite);
    }
  }
}

void Render::scaleSprite(const sf::Vector2u& texSize)
{
  const float targetSize = UiConfig::TILE_SIZE;
  float scaleX = targetSize / texSize.x;
  float scaleY = targetSize / texSize.y;

  m_sprite.setScale({scaleX, scaleY});
}

void Render::drawRelativeText(sf::RenderWindow& window,
                float xPrecent, float yPrecent, 
                const std::string& text,
                const sf::View& curView)
{
  float xPos = curView.getSize().x * xPrecent;
  float yPos = curView.getSize().y * yPrecent;
  
  unsigned int fontSize = 
                 (unsigned int)curView.getSize().y * UiConfig::FONT_SIZE_RELATIVE;
  float maxFontWidth = curView.getSize().x / GameConfig::Bar::NUM_DETAILS;

  m_text.setString(text);
  m_text.setPosition({ xPos,yPos });
  m_text.setCharacterSize(fontSize);

  sf::FloatRect bound = m_text.getLocalBounds();
  if (maxFontWidth < bound.size.x)
  {
    const float scale = bound.size.x / maxFontWidth;
    m_text.setScale({ scale,scale });
  }

  window.draw(m_text);
}
