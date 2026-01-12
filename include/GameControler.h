#pragma once
#include "WindowManger.h"
#include "FileManager.h"
#include "Level.h"
#include "IGameEvents.h"


class GameControler:public IGameEvents
{
public:
  GameControler();

  void run();

  void onCoinCollected() override;
  void onPlayerDied()    override;
  void onLevelCompleted()override;
  void onTimeRunningOut()override;
private:
  Level m_level;
  FileManager m_fm;
  WindowManager m_window;
  sf::Clock m_clock;
};