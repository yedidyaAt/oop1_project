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
  return { col, row };
}

bool Board::isValidIndex(const sf::Vector2i& index) const
{
  return (index.y >= 0 && index.y < m_levelData->m_LevelSize.y &&
         index.x >= 0 && index.x < m_levelData->m_LevelSize.x);
}


bool Board::isWall(const sf::Vector2f& pos) const
{
  sf::Vector2i index = worldToGrid(pos);

  if (!isValidIndex(index))
    return false;

  const auto& obj = (*m_map)[index.y][index.x];

  if (!obj) 
   return false;

  if (obj->getSymbol() == ObjectSymbol::WALL)
    return true;

  return false;
}

bool Board::isLadder(const sf::Vector2f& pos) const
{
  sf::Vector2i index = worldToGrid(pos);

  if (!isValidIndex(index)) 
    return false;

  const auto& obj = (*m_map)[index.y][index.x];

  if (!obj)
    return false;

  if (obj->getSymbol() == ObjectSymbol::LADDER)
    return true;

  return false;
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
  sf::Vector2i index = worldToGrid(digPos);

  if (!isValidIndex(index)) 
    return;

  // 2. שליפת האובייקט
  auto& obj =(*m_map)[index.y][index.x];

  if (obj)
  {
    if (obj->getSymbol() == ObjectSymbol::GROUND)
      obj->destroy();
  }
}

