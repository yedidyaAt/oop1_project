#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "StaticObject.h"
#include "Enemy.h"
#include <iostream> // בשביל הדיבאג
#include "GameBar.h"
#include "WindowManager.h"
#include "Factory.h"
#include "SmartEnemy.h"

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

void Level::setLevel(const std::vector<std::string>& board, LevelData& levelData)
{
  m_levelData = &levelData;

  setObjects(board);
  setBoardMoveable();
  setCoins();

  m_board.setBoard(&m_staticObj, m_player.get(), m_levelData);
}

void Level::drawLevel(sf::RenderWindow& window)
{
  drawStaticObj(window);
  drawMoveableObj(window, getMovableObj());
  m_player->draw(window);
}

bool Level::createEntity(char tile,const sf::Vector2f& pos, const sf::Vector2f& index)
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
    m_staticObj[index.y][index.x] = std::unique_ptr<StaticObject>(staticObj);
    return true;
  }

  return false;
}

void Level::setObjects(const std::vector<std::string>& board)
{
  m_movableObj.clear();
  m_staticObj.clear();

  resizeMap();

  for (int row = 0; row < board.size(); ++row)
  {
    for (int col = 0; col < board[row].size(); ++col)
    {
      const char& tile = board[row][col];
      sf::Vector2f pos(
        static_cast<float>(col) * UiConfig::TILE_SIZE,
        static_cast<float>(row) * UiConfig::TILE_SIZE
      );

      createEntity(tile, pos,sf::Vector2f{(float)col,(float)row});
    }
  }
}

void Level::setBoardMoveable()
{
  m_player->setBoradPtr(m_board);

  for (auto& obj : m_movableObj)
    obj->setBoradPtr(m_board);
}

void Level::setCoins()
{
  m_levelData->m_coinCreated = Factory::instance().getCreatedCnt(ObjectSymbol::COIN);
  m_player->setCoinCreated(m_levelData->m_coinCreated);
}

void Level::resizeMap()
{
  m_staticObj.resize(m_levelData->m_LevelSize.y);

  for (auto& row : m_staticObj) {
    row.resize(m_levelData->m_LevelSize.x);
  }
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

  for (auto& line : m_staticObj)
  {
    for (auto& obj : line)
    {
      if (obj && curObj.haveColision(*obj.get())) // obj != nullptr
      {
        curObj.handleCollision(*obj.get());
      }
    }
  }
}

void Level::updateLevel()
{
  updateObject();
  handlColisions();
}

void Level::drawMoveableObj(sf::RenderWindow& window,const std::vector<std::unique_ptr<MovingObject>>& objects) const
{
  for (const auto& obj : objects)
    if(obj)
      obj->draw(window);
}

void Level::drawStaticObj(sf::RenderWindow& window)
{
  for (const auto& line : m_staticObj)
    for (const auto& obj : line)
      if (obj)
        obj->draw(window);
}

void Level::resetPositions()
{
  for (auto& object : m_movableObj)
    object->resetStartPos();
}


const std::vector<std::unique_ptr<MovingObject>>& Level::getMovableObj() const
{
  return m_movableObj;
}

const  std::vector<std::vector<std::unique_ptr<StaticObject>>>& Level::getStaticObj() const
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
