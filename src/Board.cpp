#include "Board.h"
#include <SFML/System/Vector2.hpp>
#include "Const.h"
#include "StaticObject.h"
#include <iostream>


void Board::loadFromData(const std::vector<std::string>& data)
{
  setSizeBoard(data);
  setBoard(data);
}

ObjectSymbol Board::getSymbolAt(const sf::Vector2f& pos) const
{
  int posX = static_cast<int>(pos.y / UiConfig::TILE_SIZE);
  int posY = static_cast<int>(pos.x / UiConfig::TILE_SIZE);

  if (posX < 0 || posX >= m_board.size() || posY < 0 || posY >= m_board[0].size())
    return ObjectSymbol::WALL;

  return m_board[posX][posY]->getSymbol();
}

const std::vector<std::vector<std::unique_ptr<Object>>>& Board::getBoardObjects() const
{
  return m_board;
}

sf::Vector2f Board::getSizeBoard() const
{ 
  auto width = m_board.size() ? m_board[0].size() : 0;
    return sf::Vector2f(width,m_board.size());
}

bool Board::isHitSolid(const sf::FloatRect& rec) const
{
  sf::Vector2f topLeftRec = sf::Vector2f{   rec.position.x,rec.position.y };
  sf::Vector2f topRightRec = sf::Vector2f{  rec.position.x+ rec.size.x,
                                            rec.position.y };

  sf::Vector2f downLeftRec = sf::Vector2f{  rec.position.x,rec.position.y + rec.size.y };
  sf::Vector2f downRightRec = sf::Vector2f{ rec.position.x + rec.size.x,
                                            rec.position.y + rec.size.y };

  return isSolid(topLeftRec) || isSolid(topRightRec) || isSolid(downLeftRec) 
                                                     || isSolid(downRightRec);
}

bool Board::isSolid(ObjectSymbol sym) const
{
  return sym==ObjectSymbol::GROUND || sym == ObjectSymbol::WALL;
}

bool Board::isSolid(const sf::Vector2f& pos) const
{
  return isSolid(getSymbolAt(pos));
}

void Board::setSizeBoard(const std::vector<std::string>& data)
{
  m_board.clear();
  size_t rows = static_cast<int>(data.size());
  size_t cols = (rows > 0) ? data[0].size() : 0;

  m_board.resize(rows);

  for (auto& cell : m_board)
    cell.resize(cols);
}

void Board::setBoard(const std::vector<std::string>& data)
{
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      sf::Vector2f pos = sf::Vector2f{ static_cast<float>(j)*UiConfig::TILE_SIZE,static_cast<float>(i) * UiConfig::TILE_SIZE };

      m_board[i][j] = std::make_unique<StaticObject>(
        pos, static_cast<ObjectSymbol>(data[i][j])
      );
    }
  }
}
