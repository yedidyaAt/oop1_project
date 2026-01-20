#pragma once
#include <string_view>
#include "GameRules.h"

namespace UiConfig
{
    // Boad
  inline constexpr float TILE_SIZE = 50.f;

  //button menu size
  inline constexpr float BUTTON_WIDTH_RATIO = 0.3f;
  inline constexpr float BUTTON_HIGHT_RATIO = 0.1f;
  inline constexpr float BUTTON_FONT_SIZE_RATIO = 0.8f;
  inline constexpr float BUTTON_GAP_RATIO = 0.05f;
  inline constexpr int   BUTTON_CNT   = 3;

  //background button
  inline constexpr float BUTTON_PAD_X = 0.05f;
  inline constexpr float BUTTON_PAD_Y = 0.05f;



  //button type
  inline constexpr std::string_view  START_STR = "START";
  inline constexpr std::string_view  HELP_STR = "HELP";
  inline constexpr std::string_view  EXIT_STR = "EXIT";

}
