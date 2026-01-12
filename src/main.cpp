#include "WindowManger.h"
#include "FileManager.h"
#include "Level.h"
#include "Render.h"
#include <iostream>
#include "io.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <thread> // חובה בשביל sleep_for
#include <chrono> // חובה בשביל הגדרת הזמן
#include "SoundManager.h"
#include "GameControler.h"


int main()
{
 /*
  WindowManager window;
  Resources::instance().loadResources();
  SoundManager::instance();
  FileManager fm;
  Level level;
  Render::instance();

  sf::Clock clock;
    system("cls");
    level.setLevel(fm.getLevel(0));
    
    window.updateGameView(level);

    while (window.isOpen())
    {
      while (const auto& event = window.pollEvent())
      {
        if (event->is<sf::Event::Closed>())
          window.close();
        
        else if (const auto& resized = event->getIf<sf::Event::Resized>())
        {
          window.updateGameView(level,resized);
        }
      }

      level.run(clock);

      window.clear();
      Render::instance().draw(window, level);
      window.display();
    }
    */

  GameControler().run();
  
  


}
