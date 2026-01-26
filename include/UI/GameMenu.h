#pragma once
#include <SFML/Graphics.hpp>
#pragma once
#include "Button.h"
#include <vector>
#include "WindowManager.h"

class GameMenu
{
public:
  explicit GameMenu(WindowManager& window);

  ButtonType run();

private:
  void draw(WindowManager& window);
  void updateLayout(const sf::Vector2f& windowSize);
  void initButtons();


  ButtonType handle(const auto&) {/*igonr other event*/ return ButtonType::NONE; }
  ButtonType handle(const sf::Event::Closed& closed);
  ButtonType handle(const sf::Event::MouseMoved& mouseMoved);
  ButtonType handle(const sf::Event::MouseButtonReleased& mouseClick);
  ButtonType handle(const sf::Event::Resized& resized);


  WindowManager& m_window;
  std::vector<Button> m_buttons;
};