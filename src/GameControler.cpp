#include "GameControler.h"
#include "Render.h"
#include "Resources.h"
#include "SoundManager.h"
#include <iostream>

GameControler::GameControler():m_level(this)
{
  Resources::instance().loadResources();
  Render::instance();
  SoundManager::instance();
  m_level.setLevel(m_fm.getLevel(0));
  m_window.updateGameView(m_level);
}

void GameControler::run()
{
  while (m_window.isOpen())
  {
    while (const auto& event = m_window.pollEvent())
    {
      // Event
      if (event->is<sf::Event::Closed>())
        m_window.close();

      else if (const auto& resized = event->getIf<sf::Event::Resized>())
        m_window.updateGameView(m_level, resized);

    }

    // update

    m_level.run(m_clock);

    //draw
    m_window.clear();
    m_window.activateGameView();
    Render::instance().drawLevel(m_window,m_level);

    m_window.activateBarView();

    Render::instance().drawRelativeText(m_window,
      UiConfig::FONT_X_PRECENT_LIFE,
      UiConfig::FONT_Y_PRECNET,
      "LIFE", m_window.getView());
   
    m_window.display();
  }
}

void GameControler::onCoinCollected()
{
  SoundManager::instance().playSound(SoundType::COLLECT_COIN);

  if (!m_level.coinLeft())
    onLevelCompleted();
}

void GameControler::onPlayerDied()
{
  //if (gameScore.getlife())
  //{

  //}
  //else
  {
    SoundManager::instance().playSound(SoundType::LIFE_LOST);

    sf::sleep(sf::seconds(2.0f));

    m_level.resetPositions();
  }

}

void GameControler::onLevelCompleted()
{
}

void GameControler::onTimeRunningOut()
{
}

