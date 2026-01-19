#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ObjectSymbol.h"
#include "UiType.h"
#include "SoundType.h"
#include "FontType.h"

class Resources
{
public:
  static Resources& instance(); // Singleton

  void loadResources();

  const sf::Texture& getObjectTexture(ObjectSymbol symbol) const;

  const sf::Texture& getUiTexture(UiType type) const;

  const sf::SoundBuffer& getSoundBuffer(SoundType type) const;

  const sf::Font& getFont(FontType type) const;

private:
  Resources() = default;

  // --- Game Textures ---
  sf::Texture m_playerTexture;
  sf::Texture m_enemyTexture;
  sf::Texture m_wallTexture;
  sf::Texture m_coinTexture;
  sf::Texture m_groundTexture;
  sf::Texture m_ladderTexture;
  sf::Texture m_ropeTexture;
  sf::Texture m_emptyTexture;

  // --- UI Textures ---
  sf::Texture m_exitTexture;
  sf::Texture m_restartTexture;
  sf::Texture m_helpTexture;
  sf::Texture m_startTexture;

  // --- Audio Buffers ---
  sf::SoundBuffer m_coinBuffer;
  sf::SoundBuffer m_lifeLostBuffer;
  sf::SoundBuffer m_fallBuffer;
  sf::SoundBuffer m_smashedBuffer;
  sf::SoundBuffer m_countdownBuffer;
  sf::SoundBuffer m_levelCompleteBuffer;
  sf::SoundBuffer m_gameOverVoiceBuffer;  // הקול

  // --- Fonts ---
  sf::Font m_damned;

};