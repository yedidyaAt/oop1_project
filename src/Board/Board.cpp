#include "Board.h"
#include "Player.h" 

#include "Factory.h"
#include "LevelData.h"
#include "UiConfig.h"

#include <iostream> 


void Board::setPlayer(const Player* player)
{
  m_player = player;
}

sf::Vector2i Board::worldToGrid(const sf::Vector2f& pos) const
{
  int col = static_cast<int>(pos.x / UiConfig::TILE_SIZE);
  int row = static_cast<int>(pos.y / UiConfig::TILE_SIZE);
  return sf::Vector2i{ col, row };
}


sf::Vector2i Board::worldToGrid(const sf::Vector2i& pos) const
{
  return worldToGrid(static_cast<sf::Vector2f>(pos));
}

sf::Vector2f Board::gridToWorld(const sf::Vector2i& pos) const
{
  float col = pos.x * UiConfig::TILE_SIZE;
  float row = pos.y * UiConfig::TILE_SIZE;
  return sf::Vector2f{ row, col};
}

bool Board::isValidIndex(const sf::Vector2i& index) const
{
  return (index.x >= 0 && index.y >= 0 &&
    static_cast<unsigned int>(index.x) < m_levelData->m_LevelSize.x &&
    static_cast<unsigned int>(index.y) < m_levelData->m_LevelSize.y);
}


bool Board::isWall(const sf::Vector2f& pos) const
{
  auto index = worldToGrid(pos);

  return isWall(index);
}

bool Board::isWall(const sf::Vector2i& index) const
{
  if (!isValidIndex(index))
    return false;

  const auto& obj = (*m_map)[index.y][index.x];

  if (!obj)
    return false;

  if (obj->getSymbol() == ObjectSymbol::WALL || obj->getSymbol() == ObjectSymbol::GROUND)
    return true;

  return false;
}


bool Board::isLadder(const sf::Vector2f& pos) const
{
  auto index = worldToGrid(pos);

  if (!isValidIndex(index)) 
    return false;

  const auto& obj = (*m_map)[index.y][index.x];

  if (!obj)
    return false;

  if (obj->getSymbol() == ObjectSymbol::LADDER)
    return true;

  return false;
}

bool Board::isBoardEmpty() const
{
  if (!isHaveBoard())
    return false;

  return !m_map->size() ? true : false;
}

bool Board::isHaveBoard() const
{
  return m_map; // if is null or have som ptr 
}

void Board::setBoard(std::vector<std::vector<std::unique_ptr<StaticObject>>>* board, 
                                                                   const Player* player
                                                                  , const LevelData* levelData)
{
  setMap(board);
  setPlayer(player);
  setLevelData(levelData);
}

sf::Vector2f Board::getPlayerPosition() const
{
  if (m_player) {
    return m_player->getPos();
  }

  return { 0.f, 0.f }; 
}

sf::Vector2u Board::getSizeBoard() const
{
  if (!m_levelData)
    return { 0,0 };

  return m_levelData->m_LevelSize;
}

ObjectSymbol Board::getSymbolAt(const sf::Vector2i& index) const
{
  if (!isValidIndex(index))
    return ObjectSymbol::NONE;

 const auto& obj = (*m_map)[index.y][index.x];

 if (!obj)
   return ObjectSymbol::NONE;

 return obj->getSymbol();
}

const StaticObject* Board::getObjAt(const sf::Vector2i& index) const
{
  return (*m_map)[index.y][index.x].get();
}

void Board::setLevelData(const LevelData* levelData)
{
  m_levelData = levelData;
}

void Board::setMap(std::vector<std::vector<std::unique_ptr<StaticObject>>>* board)
{
  m_map = board;
}

void Board::tryToDig(const sf::Vector2f& digPos)
{
  auto index = worldToGrid(digPos);

  if (!isValidIndex(index)) 
    return;

 
  auto& obj =(*m_map)[index.y][index.x];

  if (obj)
  {
    if (obj->getSymbol() == ObjectSymbol::GROUND)
      obj->destroy();
  }
}

