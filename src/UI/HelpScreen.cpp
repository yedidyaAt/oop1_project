#include "HelpScreen.h"
#include "Resources.h"
#include "UiConfig.h"

#include <iostream>

HelpScreen::HelpScreen(WindowManager& window):
                  m_window(window),
                  m_textHelp(Resources::instance().getFont(FontType::Damned)),
                  m_buttonExit(Resources::instance().getFont(FontType::Damned))
{
  m_window.updateDefaultView();
  setHelpScreen();
}

void HelpScreen::run()
{
  ButtonType curStatus = ButtonType::NONE;

  while (m_window.isOpen())
  {
    while (const auto& event = m_window.pollEvent())
    {
      curStatus = event->visit([this](const auto& event) { return handle(event); });

      if (curStatus == ButtonType::EXIT)
        return;
    }

    m_window.clear();

    draw();

    m_window.display();
  }

}

void HelpScreen::setHelpScreen()
{
  // בתוך HelpScreen.cpp

  m_textHelp.setString(R"(
GAME RULES
----------------

[ CONTROLS ]
Move:       Arrows or WASD
Dig Left:   Z
Dig Right:  X
Close Help: Escape or click EXIT

[ MISSION ]
1. Run away from enemies!
2. Don't fall into the void.
3. Collect ALL coins to pass.
4. Survive until the end.

NO TURNING BACK!
)");

  m_buttonExit.setButtonType(ButtonType::EXIT);
  updateLayout();
}

void HelpScreen::updateLayout()
{
  //--------- general setting -------------------
  const float helpHeightTopPart = m_window.getView().getSize().y * UiConfig::HEIGHT_HELP_SCREEN_TOP_RATIO;
  const float helpWidth = m_window.getView().getSize().x;

  const float helpHeightbottomPart = m_window.getView().getSize().y * UiConfig::HEIGHT_HELP_SCREEN_BOTTOM_RATIO;

  const float buttonWidth = m_window.getView().getSize().x * UiConfig::BUTTON_WIDTH_RATIO;
  const float buttonHeight = helpHeightbottomPart * 0.9f;
  const float fontSize = buttonHeight * UiConfig::BUTTON_FONT_SIZE_RATIO;


  //--------- help text -------------------

  m_textHelp.setCharacterSize(fontSize);

  m_textHelp.setScale({ 1.f,1.f });
  const sf::FloatRect boundT = m_textHelp.getLocalBounds();

  if (boundT.size.x >= helpWidth || boundT.size.y >= helpHeightTopPart)
  {
    const float scaleX = helpWidth / boundT.size.x;
    const float scaleY = helpHeightTopPart / boundT.size.y;
    const float scale = std::min(scaleX, scaleY);

    m_textHelp.setScale({ scale,scale });
  }

  const float centerX = boundT.position.x + boundT.size.x / 2;
  const float cenetrY = boundT.position.y + boundT.size.y / 2;

  const float centerPosX  = helpWidth / 2;
  const float centerPosY = helpHeightTopPart / 2;

  m_textHelp.setOrigin({ centerX,cenetrY });
  m_textHelp.setPosition({ centerPosX,centerPosY });

  //--------- button text -------------------
  const float gapLeft = helpWidth * UiConfig::BUTTON_GAP_RATIO;

  m_buttonExit.setScale({ 1.f,1.f });
  m_buttonExit.setSizeAndOrigin(fontSize);

  const auto boundB = m_buttonExit.getLocalBounds();
  if (boundB.size.x >= helpWidth - gapLeft || boundB.size.y >= buttonHeight)
  {
    const float scaleX = (helpWidth - gapLeft)/ boundB.size.x;
    const float scaleY = buttonHeight / boundB.size.y;
    const float scale = std::min(scaleX, scaleY);

    m_buttonExit.setScale({ scale,scale });
  }

  float currentBtnWidth = m_buttonExit.getGlobalBounds().size.x; 

  const float posX = gapLeft + currentBtnWidth / 2;
  const float posY = m_window.getView().getSize().y - helpHeightbottomPart / 2;

  m_buttonExit.setPos(posX, posY);

}

void HelpScreen::draw()
{
  m_window.draw(m_textHelp);
  m_buttonExit.draw(m_window);
}

ButtonType HelpScreen::handle(const sf::Event::Closed& closed)
{
  (void)closed;
  m_window.close();

  return ButtonType::NONE;
}

ButtonType HelpScreen::handle(const sf::Event::Resized& resized)
{
  m_window.updateView(&resized);

  const sf::Vector2f newSize{ (float)resized.size.x,(float)resized.size.y };
  updateLayout();

  return ButtonType::NONE;
}

ButtonType HelpScreen::handle(const sf::Event::KeyReleased& key)
{
  return key.code == sf::Keyboard::Key::Escape ? ButtonType::EXIT: ButtonType::NONE;
}

ButtonType HelpScreen::handle(const sf::Event::MouseButtonReleased& mouseClick)
{
  const sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseClick.position);
  ButtonType buttonType = ButtonType::NONE;

  buttonType = m_buttonExit.handlClick(mousePos);

  if (buttonType != ButtonType::NONE)
    return buttonType;
  
  return buttonType;
}

ButtonType HelpScreen::handle(const sf::Event::MouseMoved& mouseMoved)
{
  const sf::Vector2f mousePos = m_window.mapPixelToCoords(mouseMoved.position);

  m_buttonExit.handlHover(mousePos);

  return ButtonType::NONE;
}
