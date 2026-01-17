#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "StaticObject.h" 
#include "Const.h" 

class Player;

class Board {
public:
  void setBoard(std::vector<std::vector<std::unique_ptr<StaticObject>>>* ,
                const Player*,
                const LevelData* );
  
  sf::Vector2f getPlayerPosition() const;
  sf::Vector2u getSizeBoard()const;

  bool isWall(const sf::Vector2f& pos) const;
  bool isLadder(const sf::Vector2f& pos) const;

  void tryToDig(const sf::Vector2f& digPos);
private:
  void setPlayer(const Player* player);
  void setLevelData(const LevelData* levelData);
  void setMap(std::vector<std::vector<std::unique_ptr<StaticObject>>>* board);
  sf::Vector2i worldToGrid(const sf::Vector2f& pos) const;
  bool isValidIndex(const sf::Vector2i& index) const;

  std::vector<std::vector<std::unique_ptr<StaticObject>>> *m_map = nullptr;
  const LevelData* m_levelData = nullptr;
  const Player* m_player = nullptr;
};