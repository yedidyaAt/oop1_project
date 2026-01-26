#include "Resources.h"
#include <cassert>

#include <iostream>

Resources& Resources::instance() {
  static Resources inst;
  return inst;
}

void Resources::loadResources()
{
  bool texturesLoaded =
    m_playerTexture.loadFromFile("images/objectPic/player.png") &&
    m_enemyTexture.loadFromFile("images/objectPic/enemy.png") &&
    m_wallTexture.loadFromFile("images/objectPic/wall.png") &&
    m_coinTexture.loadFromFile("images/objectPic/coin.png") &&
    m_groundTexture.loadFromFile("images/objectPic/ground.png") &&
    m_ladderTexture.loadFromFile("images/objectPic/ladder.png") &&
    m_ropeTexture.loadFromFile("images/objectPic/rope.png") &&
    m_emptyTexture.loadFromFile("images/objectPic/empty.png");
    

  bool soundsLoaded =
    m_coinBuffer.loadFromFile("sounds/gotCoin.mp3") &&
    m_lifeLostBuffer.loadFromFile("sounds/lifeLost.mp3") &&
    m_fallBuffer.loadFromFile("sounds/playerfalling.mp3") &&
    m_smashedBuffer.loadFromFile("sounds/playerSmashed.mp3") &&
    m_countdownBuffer.loadFromFile("sounds/gameCountdown.mp3") &&
    m_levelCompleteBuffer.loadFromFile("sounds/finishLevel.mp3")&&
    m_gameOverVoiceBuffer.loadFromFile("sounds/gameOverVoice.mp3")&&
    m_gtaMenuBuffer.loadFromFile("sounds/gtaMenu.wav");

  bool fontsLoaded = m_damned.openFromFile("fonts/Damned.ttf");

  if (!texturesLoaded || !soundsLoaded || !fontsLoaded) {
    std::cerr << "Error: Failed to load resources!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

const sf::Texture& Resources::getObjectTexture(ObjectSymbol symbol) const
{
  using enum ObjectSymbol; // מייבא את הסמלים כדי לחסוך כתיבה מיותרת

  switch (symbol)
  {
  case PLAYER: return m_playerTexture;
  case ENEMY:  return m_enemyTexture;
  case WALL:   return m_wallTexture;
  case COIN:   return m_coinTexture;
  case GROUND: return m_groundTexture;
  case LADDER: return m_ladderTexture;
  case ROPE:   return m_ropeTexture;
  case NONE:   return m_emptyTexture;

  default:
    assert(false && "Unknown ObjectSymbol requested!");
    return m_emptyTexture;
  }
}


const sf::SoundBuffer& Resources::getSoundBuffer(SoundType type) const {
  using enum SoundType;  // avoid rewrite

  switch (type) {
  case COLLECT_COIN:     return m_coinBuffer;
  case LIFE_LOST:        return m_lifeLostBuffer;
  case FALL:             return m_fallBuffer;
  case SMASHED:          return m_smashedBuffer;
  case COUNTDOWN:        return m_countdownBuffer;
  case LEVEL_COMPLETE:   return m_levelCompleteBuffer;
  case GAME_OVER_VOICE:  return m_gameOverVoiceBuffer;
  case GTA_MENU:         return m_gtaMenuBuffer;
  default:               return m_coinBuffer;
  }
}

const sf::Font& Resources::getFont(FontType type) const
{
  switch (type)
  {
  case FontType::Damned: return m_damned;

  default:               
    assert(false && "Warning: Attempted to use a font type that isn't implemented yet!");
    return m_damned;
  }
}



