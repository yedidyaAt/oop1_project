#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <string_view>


struct LevelData
{
  int m_curLevel;
  int m_life;
  int m_score;
  float m_timer;
};


enum class FontType
{
  Damned
};
enum class BarType
{
  LIFE,
  LEVEL,
  SCORE,
  TIMER
};

enum class UiType {
  START_BUTTON,
  EXIT_BUTTON,
  RESTART_BUTTON,
  HELP_BUTTON,
};

enum class SoundType {
  COLLECT_COIN,       // gotCoin.mp3
  LIFE_LOST,          // lifeLost.mp3
  FALL,               // playerFalling.mp3
  COUNTDOWN,          // gameCountdown.mp3
  LEVEL_COMPLETE,     // finishLevel.mp3
  GAME_OVER_JINGLE,   // gameOver.mp3 (המוזיקה)
  GAME_OVER_VOICE     // gameOverVoice.mp3 (הדיבור)
};

  enum class Action
  {
    NONE,
    DIG_LEFT,
    DIG_RIGHT
  };

  enum class Layer {
    STATIC,          // collectable
    DYNAMICS,       // Muving object
  };

  enum class ObjectSymbol : char
  {
    PLAYER = '@',
    ENEMY = '%',
    COIN = '*',
    WALL = '#',
    GROUND = '^',
    LADDER = 'H',
    ROPE = '-',
    EMPTY = ' ',
    NONE = 'N',
  };


  namespace GameConfig
  {
    namespace Physics 
    {
      inline constexpr float SPEED = 200.f;
      inline constexpr float GRAVITY = 500.f;
      inline constexpr float LADDER_SNAP_THRESHOLD = 0.2f;
    }
    namespace Bar
    {
      inline constexpr int NUM_DETAILS = 4; // life,level,score,timer <- details
      inline constexpr int LIFE = 3;
      inline constexpr int START_LEVEL = 1;
      inline constexpr int SCORE = 0;
      inline constexpr float TIMER_TIME = 30;
      inline constexpr int COIN_SCORE = 2;
      inline constexpr int COMPLETE_LEVEL_SCORE = 50;
    }
  }

  namespace WindowConfig
  {
    inline constexpr int FRAME_LIMIT = 60;
    inline constexpr unsigned int WINDOW_WIDTH = 1200;
    inline constexpr unsigned int WINDOW_HEIGHT = 800;

    inline const std::string WINDOW_TITLE = "Load Runner";
    inline const std::string DEFAULT_FILE_NAME = "Board.txt";
  };

  namespace UiConfig
  {
    inline constexpr float MENU_PERCENT = 0.2f; // 20%
    inline constexpr float BOARD_PERCENT = 0.8f; // 80%

    inline constexpr float BUTTON_PADDING_PERCENT = 0.1F;
    inline constexpr float TILE_SIZE = 50.f;

    inline constexpr float FONT_SIZE_RELATIVE = 0.5f;
    inline constexpr float FONT_WIDTH_RELATIVE = 1 / GameConfig::Bar::NUM_DETAILS;


    inline constexpr float FONT_Y_PRECNET = FONT_SIZE_RELATIVE*0.5;

    inline constexpr float FONT_X_PRECENT_LEVEL = 0.03f;
    inline constexpr float FONT_X_PRECENT_LIFE  = 0.3f;
    inline constexpr float FONT_X_PRECENT_SCORE = 0.5;
    inline constexpr float FONT_X_PRECENT_TIMER = 0.7;

    inline constexpr std::string_view LEVEL_STR = "LEVEL";
    inline constexpr std::string_view LIFE_STR  = "LIFE";
    inline constexpr std::string_view SCORE_STR = "SCORE";
    inline constexpr std::string_view TIMER_STR = "TIMER";

  };
