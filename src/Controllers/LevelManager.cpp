#include "LevelManager.h"
#include "Resources.h"
#include "SoundManager.h"
#include "WindowManager.h"

#include <iostream>

LevelManager::LevelManager(WindowManager& window):m_window(window)
{}

void LevelManager::run()
{
  setLevelData();

  for (int i = 0;i < m_fm.getTotalLevels(); i++)
  {
    m_levelData.m_LevelSize = m_fm.getSizeBoard(i);
    m_levelData.m_curLevel = i+1;
    m_level.setLevel(m_fm.getLevel(i),m_levelData);

    GameStatus gameStat =  m_level.run(m_window);

    if (gameStat == GameStatus::GAME_OVER)
      break;
  }
}

void LevelManager::setLevelData()
{
  m_levelData.m_curLevel = GameRules::START_LEVEL;
  m_levelData.m_life = GameRules::STARTING_LIVES;
  m_levelData.m_score = GameRules::START_SCORE;
  m_levelData.m_timer = GameRules::LEVEL_TIMER;
}


