#pragma once
#include <vector>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Const.h"

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
  void drawObj(sf::RenderWindow& window, const std::vector<std::unique_ptr<Object>>& objects)const;

  Player* getPlayer()const;
  const std::vector<std::unique_ptr<Object>>& getStaticObj()const;
  const std::vector<std::unique_ptr<Object>>& getMovableObj()const;

  void resetPositions();
  bool createEntity(char tile, const sf::Vector2f& pos);
  void createObjects(const std::vector<std::string>& board);
  void setObjects(const std::vector<std::string>& board);
  void setSmartEnemyTarget();
  void setCoins();

  std::unique_ptr<Player> m_player;
  std::vector<std::unique_ptr<Object>> m_movableObj;
  std::vector<std::unique_ptr<Object>> m_staticObj;
  sf::Clock m_clock;

  LevelData* m_levelData;
};