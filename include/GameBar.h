#pragma once
#include <vector>
#include "Const.h"

class Object;

class GameBar
{
public:
  GameBar();

  int getLife()const;
  int getLCurLevel()const;
  int getScore()const;
  float getTimerTime()const;

  void playerDied();
  void CoinCollected();
  void levelComplete();
  void updateTimer(float dt);
private:
  void increaseLevel();
  void addScore(int score);
  int takeCoinScore();
  int levelCompleteScore();

  int m_life = GameConfig::Bar::LIFE;
  int m_curLevel = GameConfig::Bar::START_LEVEL;
  int m_score = GameConfig::Bar::SCORE;
  float m_timerTime = GameConfig::Bar::TIMER_TIME;
};