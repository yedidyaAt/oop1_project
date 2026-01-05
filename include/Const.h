#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>


  enum class Symbol : char
  {
    PLAYER = '@',
    ENEMY = '%',
    COIN = '*',
    FLOOR = '#',
    GROUND = '^',
    LADDER = 'H',
    BAR = '-',
    DELETE = 'D',
    RESET = 'R',
    SAVE = 'S',
    EMPTY = ' ',
  };

 
  namespace Speed
  {
    inline constexpr float PER_PIXEL= 100.f;
  }

namespace Consts
{
  inline constexpr int FRAME_LIMIT = 60;
  inline constexpr unsigned int WINDOW_WIDTH = 1200;
  inline constexpr unsigned int WINDOW_HEIGHT = 800;

  inline constexpr float MENU_PERCENT = 0.2f; // 20%
  inline constexpr float BOARD_PERCENT = 0.8f; // 80%

  inline constexpr int BUTTON_CNT_OBJECT_BOARD = 7;
  inline constexpr int BUTTON_CNT = 10;
  inline constexpr float BUTTON_PADDING_PERCENT = 0.1F;

  inline const std::string WINDOW_TITLE = "Board Painter";
  inline const std::string DEFAULT_FILE_NAME = "Board.txt";

  inline const std::vector<Symbol> SYMBOL = {
   Symbol::PLAYER,
   Symbol::ENEMY,
   Symbol::COIN,
   Symbol::FLOOR,
   Symbol::GROUND,
   Symbol::LADDER,
   Symbol::BAR,
   Symbol::DELETE,
   Symbol::RESET,
   Symbol::SAVE,
   Symbol::EMPTY
  };
};
