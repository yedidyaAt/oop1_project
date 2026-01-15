#include "LevelManager.h"
#include "Resources.h"
#include "SoundManager.h"
#include <iostream>

LevelManager::LevelManager()
{
  Resources::instance().loadResources();
  SoundManager::instance();
  
}

void LevelManager::run()
{
  for (int i = 0;i < m_fm.getTotalLevels(); i++)
  {
    m_level.setLevel(m_fm.getLevel(i), m_fm.getSizeBoard(i));
    m_level.run(m_window);
  }
}


