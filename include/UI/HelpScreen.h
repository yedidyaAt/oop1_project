#pragma once

#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "Button.h"

class HelpScreen
{
public:
  HelpScreen(WindowManager& window);

  void run();

private:
  void setHelpScreen();
  void updateLayout();
  void draw();

  ButtonType handle(const auto&) {/*igonr other events*/ return ButtonType::NONE; }

  ButtonType handle(const sf::Event::Closed& closed);

  ButtonType handle(const sf::Event::Resized& resized);

  ButtonType handle(const sf::Event::KeyReleased& key);

  ButtonType handle(const sf::Event::MouseButtonReleased& mouseClick);

  ButtonType handle(const sf::Event::MouseMoved& mouseMoved);


  WindowManager& m_window;
  sf::Text m_textHelp;
  Button m_buttonExit;
};