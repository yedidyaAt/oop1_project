#pragma once
#include <vector>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Const.h"
#include "StaticObject.h"
#include "Board.h"

class WindowManager;

class Level
{
public:
  Level();


  void run(WindowManager& window);

  void setLevel(const std::vector<std::string>& board, LevelData& levelData);

  float getCols()const;
  float getRows()const;
  sf::Vector2u getSizeLevel()const;
private:
  void updateLevel();
  void updateObject();
  void handlColisions();
  void handlColision(Object& curObj);
  void drawLevel(sf::RenderWindow& window);
  void drawMoveableObj(sf::RenderWindow& window, const std::vector<std::unique_ptr<MovingObject>>& objects)const;
  void drawStaticObj(sf::RenderWindow& window);

  const  std::vector<std::vector<std::unique_ptr<StaticObject>>>& getStaticObj()const;
  const std::vector<std::unique_ptr<MovingObject>>& getMovableObj()const;

  void resetPositions();
  bool createEntity(char tile, const sf::Vector2f& pos, const sf::Vector2f& index);
  void setObjects(const std::vector<std::string>& board);
  void setBoardMoveable();
  void setCoins();

  void resizeMap();

  LevelData* m_levelData;
  std::unique_ptr<Player> m_player;
  std::vector<std::unique_ptr<MovingObject>> m_movableObj;
  std::vector<std::vector<std::unique_ptr<StaticObject>>> m_staticObj;
  Board m_board;
  sf::Clock m_clock;
};