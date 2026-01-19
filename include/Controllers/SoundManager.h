#pragma once
#include <SFML/Audio.hpp>
#include "Const.h"
#include <vector>

class SoundManager
{
public:
  static SoundManager& instance();

  void playSound(SoundType type);
private:
  SoundManager();

  static const int m_poolSize = 20;
  std::vector<sf::Sound> m_sounds;
};