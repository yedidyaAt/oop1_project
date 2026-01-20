#include "GameMenu.h"

#include "Resources.h"
#include "UiConfig.h"
#include "WindowConfig.h"

#include <iostream>

GameMenu::GameMenu(WindowManager& window)  :
  m_window(window),
  m_buttons(UiConfig::BUTTON_CNT,Resources::instance().getFont(FontType::Damned))
{
  initButtons();
}

ButtonType GameMenu::run()
{
  ButtonType curStatus = ButtonType::NONE;

  while (m_window.isOpen())
  {
    while (const auto& event = m_window.pollEvent())
    {
      curStatus =   event->visit([this](const auto& event) { return handle(event); });
    
      if (curStatus != ButtonType::NONE)
        return curStatus;
    }

    
    m_window.clear();

    draw(m_window);

    m_window.display();

  }

  return curStatus; // avoid warning
}

void GameMenu::draw(WindowManager& window)
{
  for (auto& button : m_buttons)
    button.draw(window);

}

void GameMenu::initButtons()
{
  const std::vector<ButtonType> lablesType = {
        ButtonType::START,
        ButtonType::HELP,
        ButtonType::EXIT
  };

  const float windowSizeX = WindowConfig::WIDTH;
  const float windowSizeY = WindowConfig::HEIGHT;

  for (int i = 0; i < m_buttons.size(); i++)
    m_buttons[i].setButtonType(lablesType[i]);

  updateLayout({ windowSizeX,windowSizeY });
}

ButtonType GameMenu::handle(const sf::Event::Closed& closed)
{
  (void)closed;
  m_window.close();
  
  return ButtonType::NONE;
}

ButtonType GameMenu::handle(const sf::Event::MouseMoved& mouseMoved)
{
  const sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseMoved.position);

  for (auto& bt : m_buttons)
    bt.handlHover(mousePos);

  return ButtonType::NONE;
}

ButtonType GameMenu::handle(const sf::Event::MouseButtonReleased& mouseClick)
{
  const sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseClick.position);
  ButtonType buttonType = ButtonType::NONE;

  for (auto& bt : m_buttons)
  {
    buttonType = bt.handlClick(mousePos);
    if (buttonType != ButtonType::NONE)
      return buttonType;
  }

  return buttonType;
}

ButtonType GameMenu::handle(const sf::Event::Resized& resized)
{
  m_window.updateView(&resized);

  const sf::Vector2f newSize{ (float)resized.size.x,(float)resized.size.y };
  updateLayout(newSize);

  return ButtonType::NONE;
}


void GameMenu::updateLayout(const sf::Vector2f& windowSize)
{
  //button budy
  //const float slotX = windowSize.x * UiConfig::BUTTON_WIDTH_RATIO;
  const float slotY = windowSize.y * UiConfig::BUTTON_HIGHT_RATIO;
  const float fontSize = slotY * UiConfig::BUTTON_FONT_SIZE_RATIO;
  const float gap = windowSize.y * UiConfig::BUTTON_GAP_RATIO;
  //pos and center x
  const float centerPosX = windowSize.x / 2.0f;
  
  // all block buttons
  const int n = UiConfig::BUTTON_CNT;
  float totalBlockSize = (n * slotY) + ((n - 1) * gap); // for n button have n-1 gap


  float startY = (windowSize.y/2 ) - (totalBlockSize/2); // calculate to mid window and minus have block to be at middle window


  // start set 
  float centerPosY = 0 ; //dinamic 

  for (int i = 0;i < m_buttons.size(); i++)
  {
    centerPosY = startY + slotY / 2 + i * (slotY + gap); // startY + slotY / 2 <- first element
    
    m_buttons[i].setSizeAndOrigin(fontSize);
    m_buttons[i].setPos(centerPosX, centerPosY);
  }

}
