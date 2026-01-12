#pragma once
#include <SFML/Graphics.hpp>

class Level;

class WindowManager : public sf::RenderWindow
{
public:
  WindowManager();

  // הפונקציות המקוריות שלך
  void updateGameView(const Level& level, const sf::Event::Resized* resized);
  void updateGameView(const Level& level);

  // --- תוספות (בלי לשנות שמות קיימים) ---
  // פונקציות עזר להפעלת המצלמות בזמן ציור
  void activateGameView();
  void activateBarView();

private:
  void setViewFromSize(const sf::Event::Resized* resized);

  // המשתנים החדשים לשמירת המצב
  sf::View m_gameView;
  sf::View m_barView;
};