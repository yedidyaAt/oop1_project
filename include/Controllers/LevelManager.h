#pragma once
#include "WindowManager.h"
#include "FileManager.h"
#include "Level.h"

#include "LevelData.h"


class LevelManager
{
public:
  LevelManager();

  void run();

private:
  Level m_level;
  FileManager m_fm;
  WindowManager m_window;
  LevelData m_levelData;
};