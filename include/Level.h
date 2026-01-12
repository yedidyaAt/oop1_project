#pragma once
#include <vector>
#include <string>
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Board.h"
#include "Const.h"

class IGameEvents;

class Level
{
public:
  Level() = default;
  Level(IGameEvents* eventsHandler);


  void run(sf::Clock& clock);

  sf::Vector2f getPlayerPos() const;

  void setLevel(std::vector<std::string> board);
  void resetPositions();


  bool hasFloorBelow(const sf::FloatRect& rect) const;
  bool isValidState(const sf::FloatRect& rect) const;
  sf::Vector2f calculateShift(const sf::FloatRect& failedRect, const sf::Vector2f& stepDir) const;
  sf::Vector2f getMoveTo(const sf::FloatRect& curRect, const sf::Vector2f& totalVelocity, float deltaTime) const;

  const Board& getBoard()const;
  const std::vector<std::unique_ptr<Object>>& getObject()const;
  float getRows()const;
  float getCols()const;

  int coinLeft()const;
private:
  bool createEntity(char tile,const sf::Vector2f& pos);
  void sortByLayer();
  void updateObject(float deltaTime);
  void handlColisions();
  void processCollision(Player* player,Object* obj);

  void handlPlayerVsEnemy();
  void handlPlayerVsCoin(Object* obj);
  Player* getPlayer()const;
  bool isOnLadder(const sf::FloatRect& rect) const;

  void takeCoin();

  IGameEvents* m_eventsHandler = nullptr;
  int m_coinCnt = 0;
  std::vector<std::unique_ptr<Object>> m_entities;
  Board m_board;
};