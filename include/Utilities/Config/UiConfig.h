#pragma once
#include <string_view>
#include "GameRules.h"

namespace UiConfig
{
    // Layout
    inline constexpr float MENU_PERCENT = 0.2f; 
    inline constexpr float BOARD_PERCENT = 0.8f; 
    inline constexpr float BUTTON_PADDING = 0.1f;
    inline constexpr float TILE_SIZE = 50.f;

    // Fonts & Textures
    inline constexpr float FONT_SIZE_RELATIVE = 0.5f;
    


    inline constexpr float FONT_WIDTH_RELATIVE = 1.f / GameRules::NUM_UI_DETAILS; 
    inline constexpr float FONT_Y_PERCENT = FONT_SIZE_RELATIVE * 0.5f;

    // Positions
    inline constexpr float POS_X_LEVEL = 0.03f;
    inline constexpr float POS_X_LIFE  = 0.3f;
    inline constexpr float POS_X_SCORE = 0.5f;
    
    inline constexpr float POS_X_TIMER = 0.7f;

    // Strings
    inline constexpr std::string_view STR_LEVEL = "LEVEL";
    inline constexpr std::string_view STR_LIFE  = "LIFE";
    inline constexpr std::string_view STR_SCORE = "SCORE";
    inline constexpr std::string_view STR_TIMER = "TIMER";
}
