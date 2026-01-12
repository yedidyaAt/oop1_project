#include "Resources.h"
#include <iostream>

Resources& Resources::instance() {
  static Resources inst;
  return inst;
}

void Resources::loadResources()
{
  bool texturesLoaded =
    // borad object
    m_playerTexture.loadFromFile("player.png") &&
    m_enemyTexture.loadFromFile("enemy.png") &&
    m_wallTexture.loadFromFile("wall.png") &&
    m_coinTexture.loadFromFile("coin.png") &&
    m_groundTexture.loadFromFile("ground.png") &&
    m_ladderTexture.loadFromFile("ladder.png") &&
    m_ropeTexture.loadFromFile("rope.png") &&
    m_emptyTexture.loadFromFile("empty.png") &&
    // UI
    m_exitTexture.loadFromFile("exit.png") &&
    m_restartTexture.loadFromFile("restart.png") &&
    m_helpTexture.loadFromFile("help.png") &&
    m_startTexture.loadFromFile("start.png");

  bool soundsLoaded =
    m_coinBuffer.loadFromFile("gotCoin.mp3") &&
    m_lifeLostBuffer.loadFromFile("lifeLost.mp3") &&
    m_fallBuffer.loadFromFile("playerFalling.mp3") &&
    m_countdownBuffer.loadFromFile("gameCountdown.mp3") &&
    m_levelCompleteBuffer.loadFromFile("finishLevel.mp3")&&
    //m_gameOverJingleBuffer.loadFromFile("gameOver.mp3") &&
    m_gameOverVoiceBuffer.loadFromFile("gameOverVoice.mp3");

  bool fontsLoaded = m_damned.openFromFile("Damned.ttf");

  if (!texturesLoaded || !soundsLoaded || !fontsLoaded) {
    std::cerr << "Error: Failed to load resources!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

const sf::Texture& Resources::getObjectTexture(ObjectSymbol symbol) const
{
  switch (symbol)
  {
  case ObjectSymbol::PLAYER: return m_playerTexture;
  case ObjectSymbol::ENEMY:  return m_enemyTexture;
  case ObjectSymbol::WALL:   return m_wallTexture;
  case ObjectSymbol::COIN:   return m_coinTexture;
  case ObjectSymbol::GROUND: return m_groundTexture;
  case ObjectSymbol::LADDER: return m_ladderTexture;
  case ObjectSymbol::ROPE:   return m_ropeTexture;
    
  default:                   return m_emptyTexture;
  }
}

const sf::Texture& Resources::getUiTexture(UiType type) const
{
  switch (type)
  {
  case UiType::START_BUTTON:   return m_startTexture;
  case UiType::EXIT_BUTTON:    return m_exitTexture;
  case UiType::RESTART_BUTTON: return m_restartTexture;
  case UiType::HELP_BUTTON:    return m_helpTexture;
  default:                     return m_startTexture;
  }
}

const sf::SoundBuffer& Resources::getSoundBuffer(SoundType type) const
{
  switch (type)
  {
  case SoundType::COLLECT_COIN:     return m_coinBuffer;
  case SoundType::LIFE_LOST:        return m_lifeLostBuffer;
  case SoundType::FALL:             return m_fallBuffer;
  case SoundType::COUNTDOWN:        return m_countdownBuffer;
  case SoundType::LEVEL_COMPLETE:   return m_levelCompleteBuffer;
  case SoundType::GAME_OVER_JINGLE: return m_gameOverJingleBuffer;
  case SoundType::GAME_OVER_VOICE:  return m_gameOverVoiceBuffer;
  default:                          return m_coinBuffer; // сън Safe Fallback
  }
}

const sf::Font& Resources::getFont(FontType type) const
{
  switch (type)
  {
  case FontType::Damned: return m_damned;
  default:               return m_damned;
  }
}

