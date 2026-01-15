#pragma once
#include <vector>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "Const.h"

class WindowManager;

class Level
{
public:
  Level() = default;


  void run(WindowManager& window);

  void setLevel(std::vector<std::string> board, const sf::Vector2u& boardSize);

  float getCols()const;
  float getRows()const;
  sf::Vector2u getSizeLevel()const;
private:
  void updateLevel();
  void updateObject();
  void handlColisions();
  void handlColision(Object& curObj);
  void drawLevel(sf::RenderWindow& window);
  void drawObj(sf::RenderWindow& window, const std::vector<std::unique_ptr<Object>>& objects)const;
  
  Player* getPlayer()const;
  const std::vector<std::unique_ptr<Object>>& getStaticObj()const;
  const std::vector<std::unique_ptr<Object>>& getMovableObj()const;

  void resetPositions();
  bool createEntity(char tile,const sf::Vector2f& pos);
  void sortByLayer();

  std::vector<std::unique_ptr<Object>> m_movableObj;
  std::vector<std::unique_ptr<Object>> m_staticObj;
  sf::Vector2u m_sizeLevel;
  sf::Clock m_clock;
};