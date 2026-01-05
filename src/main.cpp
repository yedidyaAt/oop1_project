#pragma once
#include "FileManager.h"
#include "Level.h"
#include <iostream>
#include "io.h"
#include <cstdlib>
#include <thread> // חובה בשביל sleep_for
#include <chrono> // חובה בשביל הגדרת הזמן

int main()
{
  FileManager fm;
  Level level;

  int levelsCnt = fm.getTotalLevels();
  
  //std::cout << levelsCnt << std::endl;

  for(int i=0 ;i<levelsCnt; i++)
  {
    system("cls");
    Screen::resetLocation();
    level.setLevel(fm.getLevel(i));
    level.run();
    Screen::setLocations({0.f,fm.getSizeBoard(i).y});
    std::this_thread::sleep_for(std::chrono::seconds(3));
  }
}
