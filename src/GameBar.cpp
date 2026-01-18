#include "GameBar.h"
#include "Resources.h"
#include "string"


GameBar::GameBar()
  :m_scoreText(Resources::instance().getFont(FontType::Damned)),
   m_livesText(Resources::instance().getFont(FontType::Damned)),
   m_timeText(Resources::instance().getFont(FontType::Damned)),
   m_levelText(Resources::instance().getFont(FontType::Damned))
{
  initTexts();
}

void GameBar::drawText(WindowManager& window)
{
  window.draw(m_levelText);
  window.draw(m_livesText);
  window.draw(m_scoreText);
  window.draw(m_timeText);
}

void GameBar::update()
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

void GameBar::initTexts()
{
  
  m_levelText.setString("LEVEL");
  m_livesText.setString("LIVE");
  m_scoreText.setString("SCORE");
  m_timeText.setString("TIMER");
}

void GameBar::alignTextToSlot(sf::Text& text, int slotIndex, int totalSlots, const sf::Vector2f& barSize)
{
  const float slotWidth = barSize.x / totalSlots;

  //setSize char
  const  unsigned int charSize = barSize.y * 0.5f; // 50% from the high
  text.setCharacterSize(charSize);

  //center of text
  sf::FloatRect bound = text.getLocalBounds();
  const float centerX = bound.position.x + bound.size.x / 2;
  const float centerY = bound.position.y + bound.size.y / 2;

  text.setOrigin({ centerX,centerY});

  // cneter of slot
 const float posX = slotIndex * slotWidth + slotWidth / 2;
 const float posY = barSize.y / 2;

  text.setPosition({ posX,posY});
}
