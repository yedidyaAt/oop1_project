#pragma once
#include <vector>
#include "WindowManager.h"

class Object;
struct LevelData;;

class GameBar
{
public:
  GameBar();

  void drawText(WindowManager& window);
  void update(const sf::Vector2f& size);


  void setLevelData(const LevelData& levelData);
private:
  void updateBar();
  void updateLayout(const sf::Vector2f& size);
  void initTexts();
  void alignTextToSlot(sf::Text& text, int slotIndex, int totalSlots, const sf::Vector2f& barSize);
  
  sf::Text m_scoreText;
  sf::Text m_livesText;
  sf::Text m_timeText;
  sf::Text m_levelText;
  const LevelData* m_levelData = nullptr;
};