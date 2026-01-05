#include "Level.h"
#include <SFML/System/Vector2.hpp>
#include "DumbEnemy.h"
#include "SmartEnemy.h"
#include "StaticObject.h"


Level::Level(std::vector<std::string>& board)
{
  setLevel(board);
}

void Level::run() const
{
  draw();
}

void Level::setLevel(std::vector<std::string> board)
{
  // reset 
  m_enemies.clear();
  m_coins.clear();
  m_player.reset();

  for (int row = 0; row < board.size(); ++row)
  {
    for (int col = 0; col < board[row].size(); ++col)
    {
      char& tile = board[row][col]; 
      sf::Vector2f pos(static_cast<float>(col), static_cast<float>(row));

      if (createEntity(tile, pos)) {
        tile = ' '; 
      }
    }
  }

  m_board.loadFromData(board);
}

bool Level::createEntity(char tile, sf::Vector2f pos)
{
  switch (static_cast<Symbol>(tile))
  {
  case Symbol::PLAYER:
    m_player = std::make_unique<Player>(pos);
    return true;

  case Symbol::ENEMY:
    m_enemies.push_back(std::make_unique<DumbEnemy>(pos));
    return true;

  case Symbol::COIN:
    m_coins.push_back(std::make_unique<StaticObject>(pos, Symbol::COIN));
    return true;

  default:
    return false; 
  }
}

void Level::resetPositions()
{
  m_player->reset();

  for (auto& enemy : m_enemies) {
    enemy->reset(); 
  }
}

void Level::draw() const
{
  m_board.draw();
  
  for (const auto& entity : m_coins)
    entity->draw();

  for (const auto& entity : m_enemies)
    entity->draw();

  m_player->draw();
}


