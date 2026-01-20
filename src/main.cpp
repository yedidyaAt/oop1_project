#include "LevelManager.h"
#include "GameMenu.h"
#include "WindowManager.h"
#include "Resources.h"
#include <iostream>

int main()
{
  //LevelManager().run();

  Resources::instance().loadResources();
  WindowManager window;
  ButtonType type;

  while (window.isOpen())
  {
    type = GameMenu(window).run();

    switch (type)
    {
    case ButtonType::NONE:
      std::cout << "you click NONE" << std::endl;
      break;
    case ButtonType::START:
      std::cout << "you click START" << std::endl;
      break;
    case ButtonType::HELP:
      std::cout << "you click HELP" << std::endl;
      break;
    case ButtonType::EXIT:
      std::cout << "you click EXIT" << std::endl;
      break;
    default:
      break;
    }
  }
}
