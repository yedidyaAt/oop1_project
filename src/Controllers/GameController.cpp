#include "GameController.h"

#include "Resources.h"
#include "SoundManager.h"
#include "Factory.h"

GameController::GameController():m_window(), m_menu(m_window), m_levels(m_window)
{
  std::srand(std::time(nullptr));
  Resources::instance().loadResources();
  Factory::instance();
  SoundManager::instance();
}

void GameController::run()
{
  while (m_window.isOpen())
  {
    ButtonType type = m_menu.run();

    switch (type)
    {
    case ButtonType::START:
      m_levels.run();
      break;
    case ButtonType::HELP:
      //std::cout << "you click HELP" << std::endl;
      break;
    case ButtonType::EXIT:
      //std::cout << "you click EXIT" << std::endl;
      m_window.close();
      break;
    default:
      break;
    }

  }

}