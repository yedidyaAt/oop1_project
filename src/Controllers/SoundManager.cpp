
#include "SoundManager.h"
#include "Resources.h"
#include "SoundType.h"

#include <iostream>

SoundManager& SoundManager::instance()
{
  static SoundManager ins;
  return ins;
}

SoundManager::SoundManager()
{
  m_sounds.reserve(m_poolSize);

  const sf::SoundBuffer& tempBuffer = Resources::instance().getSoundBuffer(SoundType::COLLECT_COIN);
  
  for (int i = 0; i < m_poolSize; ++i)
  {
    m_sounds.emplace_back(tempBuffer);
  }
}

void SoundManager::playSound(SoundType type)
{

  const sf::SoundBuffer& buffer= Resources::instance().getSoundBuffer(type);


  for (auto& sound : m_sounds)
  {
    if (sound.getStatus() == sf::Sound::Status::Stopped)
    {
      sound.setBuffer(buffer);
      sound.setVolume(20.f);
      sound.play();
      break;
    }
  }
}

void SoundManager::playMusic(const std::string& fileName,int volume, bool loop)
{
  if (m_bgMusic.getStatus() == sf::Music::Status::Playing && m_curMusicName == fileName)
  {
    return;
  }
  else
    stopMusic();

  if (!m_bgMusic.openFromFile(fileName))
    return;
  
  m_curMusicName = fileName;
  m_bgMusic.setLooping(loop);
  m_bgMusic.setVolume(volume);
  m_bgMusic.play(); 
}

void SoundManager::stopMusic()
{
  m_curMusicName = "";
  m_bgMusic.stop();
}

