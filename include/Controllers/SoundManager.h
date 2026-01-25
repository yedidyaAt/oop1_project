#pragma once
#include <SFML/Audio.hpp>
#include <vector>

#include "SoundType.h"

class SoundManager
{
public:
  static SoundManager& instance();

  void playSound(SoundType type);
  void playMusic(const std::string& fileName,int volume,bool loop);
  void stopMusic();
private:
  SoundManager();

  static const int m_poolSize = 20;
  std::vector<sf::Sound> m_sounds;

  sf::Music m_bgMusic;
  std::string m_curMusicName = "";
};