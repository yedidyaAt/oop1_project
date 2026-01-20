#pragma once
#include <SFML/Graphics.hpp>

class Level;

class WindowManager : public sf::RenderWindow
{
public:
  WindowManager();
  
  void updateDefaultView();
  void updateView(const sf::Event::Resized* resized);

  void updateGameView(const Level& level, const sf::Event::Resized* resized);
  void updateGameView(const Level& level);

  // --- תוספות (בלי לשנות שמות קיימים) ---
  // פונקציות עזר להפעלת המצלמות בזמן ציור
  void activateGameView();
  void activateBarView();

  sf::Vector2f getSizeBar()const;
private:
  void setViewFromSize(const sf::Event::Resized* resized);

  // המשתנים החדשים לשמירת המצב
  sf::View m_gameView;
  sf::View m_barView;
};