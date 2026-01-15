#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "DumbEnemy.h"
#include "SmartEnemy.h"
#include <iostream> // בשביל הדיבאג
#include "GameBar.h"
#include "WindowManager.h"


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

void Level::setLevel(std::vector<std::string> board,const sf::Vector2u& boardSize)
{
  m_sizeLevel = boardSize;
  // reset 
  m_movableObj.clear();

  for (int row = 0; row < board.size(); ++row)
  {
    for (int col = 0; col < board[row].size(); ++col)
    {
      char& tile = board[row][col]; 
      sf::Vector2f pos(static_cast<float>(col)*UiConfig::TILE_SIZE, static_cast<float>(row)*UiConfig::TILE_SIZE);

      if (createEntity(tile, pos)) {
        tile = ' '; 
      }
    }
  }

  //sortByLayer();
}

void Level::drawLevel(sf::RenderWindow& window)
{
  drawObj(window, getStaticObj());
  drawObj(window, getMovableObj());
}

bool Level::createEntity(char tile,const sf::Vector2f& pos)
{
  ObjectSymbol symbol = static_cast<ObjectSymbol>(tile);

  switch (symbol)
  {
  case ObjectSymbol::PLAYER:
    m_movableObj.push_back(std::make_unique<Player>(pos));
    return true;

  case ObjectSymbol::ENEMY:
    m_movableObj.push_back(std::make_unique<DumbEnemy>(pos));
    return true;

    // --- איסוף ---
  case ObjectSymbol::COIN:
    //m_coinCnt++; // עדכון המונה הפנימי של הלבל
    // השינוי החשוב: יצירת מחלקת Coin ייעודית שיודעת להיאסף
    m_staticObj.push_back(std::make_unique<Coin>(pos));
    return true;

    // --- סביבה סטטית (עכשיו לכל אחד מחלקה משלו) ---
  case ObjectSymbol::WALL:
    m_staticObj.push_back(std::make_unique<Wall>(pos));
    return true;

  case ObjectSymbol::GROUND:
    m_staticObj.push_back(std::make_unique<Ground>(pos));
    return true;

  case ObjectSymbol::LADDER:
    m_staticObj.push_back(std::make_unique<Ladder>(pos));
    return true;

  case ObjectSymbol::ROPE:
    m_staticObj.push_back(std::make_unique<Rope>(pos));
    return true;

    // --- מקרים של התעלמות ---
  case ObjectSymbol::EMPTY:
  case ObjectSymbol::NONE:
  default:
    return false; // לא נוצר שום אובייקט (אוויר)
  }
}

void Level::updateObject()
{
  const float deltaTime = m_clock.restart().asSeconds();

  for (auto& object : m_movableObj)
    object->update(deltaTime);
}

void Level::handlColisions()
{
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

//no needs
void Level::sortByLayer() 
{
  std::sort(m_movableObj.begin(), m_movableObj.end(),
    [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) 
    { 
      return a->getLayer() < b->getLayer();
    });
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
  return m_sizeLevel;
}
