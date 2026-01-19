#include "LevelManager.h"
#include "Resources.h"
#include "SoundManager.h"
#include <iostream>
#include "Const.h"

LevelManager::LevelManager()
{
  std::srand(std::time(nullptr));
  Resources::instance().loadResources();
  SoundManager::instance();
  
}

void LevelManager::run()
{
  for (int i = 0;i < m_fm.getTotalLevels(); i++)
  {
    m_levelData.m_LevelSize = m_fm.getSizeBoard(i);
    m_levelData.m_curLevel = i+1;
    m_level.setLevel(m_fm.getLevel(i),m_levelData);

    GamePlayStat gameStat =  m_level.run(m_window);

    if (gameStat == GamePlayStat::GAME_OVER)
      break;
  }
}


