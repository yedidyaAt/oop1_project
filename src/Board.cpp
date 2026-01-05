#include "Board.h"
#include <SFML/System/Vector2.hpp>
#include "Const.h"
#include "StaticObject.h"
#include <iostream>

void Board::draw()const
{
  for (const auto& line : m_board)
  {
    for (const auto& entity : line)
      entity->draw();

    //std::cout << std::endl;
  }
}

void Board::loadFromData(const std::vector<std::string>& data)
{
  setSizeBoard(data);
  setBoard(data);
}

const std::vector<std::vector<std::unique_ptr<Object>>>& Board::getBoard() const
{
  return m_board;
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
      sf::Vector2f pos = sf::Vector2f{ static_cast<float>(j),static_cast<float>(i)};

      m_board[i][j] = std::make_unique<StaticObject>(
        pos, static_cast<Symbol>(data[i][j])
      );
    }
  }
}
