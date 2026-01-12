#include "GameBar.h"
#include "StaticObject.h"
#include <SFML/System/Vector2.hpp>


GameBar::GameBar()
{

}

int GameBar::getLife() const
{
  return m_life;
}

int GameBar::getLCurLevel() const
{
  return m_curLevel;
}

int GameBar::getScore() const
{
  return m_score;
}

float GameBar::getTimerTime() const
{
  return m_timerTime;
}

void GameBar::playerDied()
{
  m_life--;
}

void GameBar::increaseLevel()
{
  m_curLevel++;
}

void GameBar::CoinCollected()
{
  addScore(takeCoinScore());
}

void GameBar::levelComplete()
{
  addScore(levelCompleteScore());
  increaseLevel();
}

void GameBar::addScore(int score)
{
  m_score += score;
}

void GameBar::updateTimer(float dt)
{
  m_timerTime -= dt;
}

int GameBar::takeCoinScore()
{
  return GameConfig::Bar::COIN_SCORE*getLCurLevel();
}

int GameBar::levelCompleteScore()
{
  return GameConfig::Bar::COMPLETE_LEVEL_SCORE*getLCurLevel();
}

