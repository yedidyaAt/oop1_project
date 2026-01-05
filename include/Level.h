#pragma once
#include <vector>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "Const.h"

class Level
{
public:
  Level() = default;
  Level(std::vector<std::string> & map);

  void run()const;

  void setLevel(std::vector<std::string> board);
  void resetPositions();
private:
  bool createEntity(char tile, sf::Vector2f pos);
  void draw()const;
    
  std::unique_ptr<Player> m_player;
  std::vector<std::unique_ptr<Enemy>> m_enemies;
  std::vector<std::unique_ptr<Object>> m_coins;
  Board m_board;
};