#pragma once
#pragma once
#include <vector>
#include <memory>
#include "Object.h"

#include <string>


class Board
{
public:
  void loadFromData(const std::vector<std::string>& data);

  ObjectSymbol getSymbolAt(const sf::Vector2f& pos) const;
  const std::vector<std::vector<std::unique_ptr<Object>>>& getBoardObjects()const;
  sf::Vector2f getSizeBoard()const;

  bool isHitSolid(const sf::FloatRect& rec)const;
  bool isSolid(ObjectSymbol sym)const;
  bool isSolid(const sf::Vector2f& pos)const;

private:
  void setSizeBoard(const std::vector<std::string>& data);
  void setBoard(const std::vector<std::string>& data);

  std::vector<std::vector<std::unique_ptr<Object>>> m_board;
};