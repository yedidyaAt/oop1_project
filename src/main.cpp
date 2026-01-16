#include "WindowManager.h"
#include "FileManager.h"
#include "Level.h"
#include <iostream>
#include "io.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <thread> // חובה בשביל sleep_for
#include <chrono> // חובה בשביל הגדרת הזמן
#include "SoundManager.h"
#include "LevelManager.h"


int main()
{
  std::srand(std::time(nullptr));
  //WindowManager window;
  //Resources::instance().loadResources();
  //SoundManager::instance();
  //Render::instance();
  //FileManager fm;
  //Level level;

  //sf::Clock clock;
  //  system("cls");
  //  level.setLevel(fm.getLevel(0));
  //  
  //  window.updateGameView(level);

  //  while (window.isOpen())
  //  {
  //    while (const auto& event = window.pollEvent())
  //    {
  //      if (event->is<sf::Event::Closed>())
  //        window.close();
  //      
  //      else if (const auto& resized = event->getIf<sf::Event::Resized>())
  //      {
  //        window.updateGameView(level,resized);
  //      }
  //    }

  //    window.clear();
  //    level.run(window);
  //    window.display();
  //  }
  //  

  LevelManager().run();
  
  


}
