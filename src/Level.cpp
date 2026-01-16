#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "StaticObject.h"
#include "Enemy.h"
#include <iostream> // בשביל הדיבאג
#include "GameBar.h"
#include "WindowManager.h"
#include "Factory.h"

Level::Level():m_levelData(nullptr)
{
}

void Level::run(WindowManager& window)
{
  window.updateGameView(*this);

  while (window.isOpen())
  {
    while (const auto& event = window.pollEvent())
    {
      // Event
      if (event->is<sf::Event::Closed>())
        window.close();

      else if (const auto& resized = event->getIf<sf::Event::Resized>())
        window.updateGameView(*this, resized);

      else if (const auto& exitG = event->getIf<sf::Event::KeyPressed>())
      {
        if (exitG->code == sf::Keyboard::Key::Escape)
          return;
      }
    }

    // update
    updateLevel();

    //draw
    window.clear();
    window.activateGameView();
    drawLevel(window);

    window.display();
  }
}

void Level::setLevel(std::vector<std::string> board, LevelData& levelData)
{
  m_levelData = &levelData;
  // reset 
  m_movableObj.clear();

  for (int row = 0; row < board.size(); ++row)
  {
    for (int col = 0; col < board[row].size(); ++col)
    {
      char& tile = board[row][col];
      sf::Vector2f pos(
        static_cast<float>(col) * UiConfig::TILE_SIZE,
        static_cast<float>(row) * UiConfig::TILE_SIZE
      );

      createEntity(tile, pos);
    }
  }
   
  m_levelData->m_coinCreated = Factory::instance().getCreatedCnt(ObjectSymbol::COIN);
  m_player->setCoinCreated(m_levelData->m_coinCreated);
}

void Level::drawLevel(sf::RenderWindow& window)
{
  drawObj(window, getStaticObj());
  drawObj(window, getMovableObj());
  m_player->draw(window);
}

bool Level::createEntity(char tile,const sf::Vector2f& pos)
{
  ObjectSymbol symbol = static_cast<ObjectSymbol>(tile);

  auto obj = Factory::instance().creator(symbol,pos,*m_levelData);

  if (auto player = dynamic_cast<Player*>(obj.get()))
  {
    obj.release();
    m_player.reset(player);
    return true;
  }
  else if (auto enemy = dynamic_cast<Enemy*>(obj.get()))
  {
    obj.release();
    m_movableObj.push_back(std::unique_ptr<Enemy>(enemy));
    return true;
  }
  else if(auto staticObj = dynamic_cast<StaticObject*>(obj.get()))
  {
    obj.release();
    m_staticObj.push_back(std::unique_ptr<StaticObject>(staticObj));
    return true;
  }

  return false;
}

void Level::updateObject()
{
  const float deltaTime = m_clock.restart().asSeconds();

  m_player->update(deltaTime);

  for (auto& object : m_movableObj)
    object->update(deltaTime);
}

void Level::handlColisions()
{
  handlColision(*m_player.get());

  for (auto& obj : m_movableObj)
  {
    handlColision(*obj.get());
  }
}

void Level::handlColision(Object& curObj)
{
  for (auto& obj : m_movableObj)
  {
    if (curObj.haveColision(*obj.get()))
    {
      curObj.handleCollision(*obj.get());
    }
  }

  for (auto& obj : m_staticObj)
  {
    if (curObj.haveColision(*obj.get()))
    {
      curObj.handleCollision(*obj.get());
    }
  }
}

void Level::updateLevel()
{
  updateObject();
  handlColisions();
}

void Level::drawObj(sf::RenderWindow& window,const std::vector<std::unique_ptr<Object>>& objects) const
{
  for (const auto& obj : objects)
    obj->draw(window);
}

void Level::resetPositions()
{
  for (auto& object : m_movableObj)
    object->resetStartPos();
}

Player* Level::getPlayer() const
{
  for (const auto& obj : m_movableObj)
    if (obj->getSymbol() == ObjectSymbol::PLAYER)
      return static_cast<Player*>(obj.get());

  return nullptr;
}

const std::vector<std::unique_ptr<Object>>& Level::getMovableObj() const
{
  return m_movableObj;
}

const std::vector<std::unique_ptr<Object>>& Level::getStaticObj() const
{
  return m_staticObj;
}

float Level::getCols() const
{
  return getSizeLevel().x;
}

float Level::getRows() const
{
  return getSizeLevel().y;
}

sf::Vector2u Level::getSizeLevel() const
{
  if(m_levelData)
  return m_levelData->m_LevelSize;
  else
  {
    std::cerr << "you dumb ass." << std::endl;
    return sf::Vector2u();
  }
}
