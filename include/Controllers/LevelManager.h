#pragma once
#include "WindowManager.h"
#include "FileManager.h"
#include "Level.h"

#include "LevelData.h"


class LevelManager
{
public:
  explicit LevelManager(WindowManager& window);

  void run();

private:
  void setLevelData();

  WindowManager& m_window;
  FileManager m_fm;
  LevelData m_levelData;
  Level m_level;
};