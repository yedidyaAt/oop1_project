#include "GameBar.h"
#include "Resources.h"
#include "string"
#include "LevelData.h"
#include "FontType.h"


GameBar::GameBar()
  :m_scoreText(Resources::instance().getFont(FontType::Damned)),
   m_livesText(Resources::instance().getFont(FontType::Damned)),
   m_timeText(Resources::instance().getFont(FontType::Damned)),
   m_levelText(Resources::instance().getFont(FontType::Damned))
{
}

void GameBar::drawText(WindowManager& window)
{
  window.draw(m_levelText);
  window.draw(m_livesText);
  window.draw(m_scoreText);
  window.draw(m_timeText);
}

void GameBar::update(const sf::Vector2f& size)
{
  updateBar();
  updateLayout(size);
}

void GameBar::updateBar()
{
  if (!m_levelData)
    return;

  m_levelText.setString("LEVEL: " + std::to_string(m_levelData->m_curLevel));
  m_livesText.setString("LIVE: "  + std::to_string(m_levelData->m_life));
  m_scoreText.setString("SCORE: " + std::to_string(m_levelData->m_score));
  m_timeText.setString("TIMER: "  + std::to_string(static_cast<int>(m_levelData->m_timer)));
}

void GameBar::updateLayout(const sf::Vector2f& size)
{
  alignTextToSlot(m_levelText, 0, 4, size);
  alignTextToSlot(m_livesText, 1, 4, size);
  alignTextToSlot(m_scoreText, 2, 4, size);
  alignTextToSlot(m_timeText , 3, 4, size);
}

void GameBar::setLevelData(const LevelData& levelData)
{
  m_levelData = &levelData;
}

void GameBar::alignTextToSlot(sf::Text& text, int slotIndex, int totalSlots, const sf::Vector2f& barSize)
{
  text.setScale({1.f, 1.f});
  const float slotWidth = barSize.x / totalSlots;
  //const float slotHight = barSize.y / totalSlots;

  //setSize char
  const  unsigned int charSize = barSize.y * 0.5f; // 50% from the high
  text.setCharacterSize(charSize);

  //center of text
  sf::FloatRect bound = text.getLocalBounds();
  const float centerX = bound.position.x + bound.size.x / 2;
  const float centerY = bound.position.y + bound.size.y / 2;

  text.setOrigin({ centerX,centerY});

  // scale 
  if (slotWidth < bound.size.x)
  {
    const float scaleX = slotWidth / bound.size.x;
    const float scaleY = charSize / bound.size.y;

    const float scale = std::min(scaleX, scaleY);
    text.setScale({scale, scale});
  }

  // cneter of slot
 const float posX = slotIndex * slotWidth + slotWidth / 2;
 const float posY = barSize.y / 2;

  text.setPosition({ posX,posY});
}
