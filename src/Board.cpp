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

//ObjectSymbol Board::getSymbolAt(const sf::Vector2f& pos) const
//{
//  int posX = static_cast<int>(pos.y / UiConfig::TILE_SIZE);
//  int posY = static_cast<int>(pos.x / UiConfig::TILE_SIZE);
//
//  if (posX < 0 || posX >= m_board.size() || posY < 0 || posY >= m_board[0].size())
//    return ObjectSymbol::WALL;
//
//  return m_board[posX][posY]->getSymbol();
//}

const std::vector<std::unique_ptr<Object>>& Board::getBoardObjects() const
{
  return m_staticObj;
}

//sf::Vector2f Board::getSizeBoard() const
//{ 
//  auto width = m_board.size() ? m_board[0].size() : 0;
//    return sf::Vector2f(width,m_board.size());
//}
//
//bool Board::isHitSolid(const sf::FloatRect& rec) const
//{
//  sf::Vector2f topLeftRec = sf::Vector2f{   rec.position.x,rec.position.y };
//  sf::Vector2f topRightRec = sf::Vector2f{  rec.position.x+ rec.size.x,
//                                            rec.position.y };
//
//  sf::Vector2f downLeftRec = sf::Vector2f{  rec.position.x,rec.position.y + rec.size.y };
//  sf::Vector2f downRightRec = sf::Vector2f{ rec.position.x + rec.size.x,
//                                            rec.position.y + rec.size.y };
//
//  return isSolid(topLeftRec) || isSolid(topRightRec) || isSolid(downLeftRec) 
//                                                     || isSolid(downRightRec);
//}
//
//bool Board::isSolid(ObjectSymbol sym) const
//{
//  return sym==ObjectSymbol::GROUND || sym == ObjectSymbol::WALL;
//}
//
//bool Board::isSolid(const sf::Vector2f& pos) const
//{
//  return isSolid(getSymbolAt(pos));
//}

void Board::draw(sf::RenderWindow& window)
{
  for (const auto& obj : m_staticObj)
    obj->draw(window);
}

void Board::setSizeBoard(const std::vector<std::string>& data)
{
  m_staticObj.clear();
  size_t rows = static_cast<int>(data.size());

  m_staticObj.reserve(rows);
}

void Board::setBoard(const std::vector<std::string>& data)
{
  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].size(); j++) {
      sf::Vector2f pos = sf::Vector2f{ static_cast<float>(j)*UiConfig::TILE_SIZE,static_cast<float>(i) * UiConfig::TILE_SIZE };

      createEntity(data[i][j], pos);
    }
  }
}

bool Board::createEntity(char tile, const sf::Vector2f& pos)
{
  // המרה מ-char ל-Enum כדי שה-Switch יהיה קריא
  ObjectSymbol symbol = static_cast<ObjectSymbol>(tile);

  switch (symbol)
  {
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
