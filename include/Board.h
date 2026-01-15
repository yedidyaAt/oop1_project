#pragma once
#include <vector>
#include <memory>
#include "Object.h"

#include <string>

#include "Coin.h"
#include "Wall.h"
#include "Ground.h"
#include "Ladder.h"
#include "Rope.h"


class Board
{
public:
  void loadFromData(const std::vector<std::string>& data);

  //ObjectSymbol getSymbolAt(const sf::Vector2f& pos) const;
  const std::vector<std::unique_ptr<Object>>& getBoardObjects()const;

  
  void draw(sf::RenderWindow& window);
private:
  void setSizeBoard(const std::vector<std::string>& data);
  void setBoard(const std::vector<std::string>& data);
  bool createEntity(char tile, const sf::Vector2f& pos);

  std::vector<std::unique_ptr<Object>> m_staticObj;
};