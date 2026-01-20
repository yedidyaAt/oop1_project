#pragma once
#include "WindowManager.h"
#include "LevelManager.h"
#include "GameMenu.h"

class GameController
{
public:
  GameController();

  void run();


private:
  WindowManager m_window;
  GameMenu m_menu;
  LevelManager m_levels;
};