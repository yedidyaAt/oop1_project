#include "SmartEnemy.h"

#include "Enemy.h"
#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Wall.h"

#include "InputHandler.h"
#include "UiConfig.h"
#include <queue>
#include <iostream>

SmartEnemy::SmartEnemy(const sf::Vector2f& position, bool isActive)
  :Enemy(position, isActive) {
}


void SmartEnemy::update(float deltaTime, const LevelData* /*levelData*/)
{
  if (!isActive())
    return;

  move(deltaTime);
  keepObjInsideMap();
  checkFallingOutsideMap();
}

void SmartEnemy::handleCollision(Object& obj)
{
  obj.handleCollision(*this);
}
void SmartEnemy::handleCollision(Player& obj)
{
  obj.handleCollision(*this);
}
void SmartEnemy::handleCollision(Enemy& /*obj*/)
{
}
void SmartEnemy::handleCollision(Coin& /*obj*/)
{
}
void SmartEnemy::handleCollision(Wall& obj)
{
  resolveOverlap(obj);
}
void SmartEnemy::handleCollision(Ground& obj)
{
  resolveOverlap(obj);
}
void SmartEnemy::handleCollision(Ladder& obj)
{
  if (isOnObject(obj))
  {
    setOnLadder(true);
    handleLadderLogic(obj);
  }
}
void SmartEnemy::handleCollision(Rope& obj)
{
  handleRopeLogic(obj);
}

sf::Vector2f SmartEnemy::getDirection() 
{
  return getSmartNextDir(getPos(), getBoard()->getPlayerPosition());
}

sf::Vector2f SmartEnemy::getHafeSmartDir() const
{
  if (!getBoard())
    return { 0, 0 };


  sf::Vector2f myPos = getPos();
  sf::Vector2f playerPos = getBoard()->getPlayerPosition();

  sf::Vector2f dir = { 0, 0 };

  float diffX = playerPos.x - myPos.x;
  float diffY = playerPos.y - myPos.y;

  if (isOnLadder())
  {
    if (std::abs(diffY) > 10.f)
    {
      dir.y = (diffY > 0) ? 1.f : -1.f;
      return dir;
    }
  }

  if (std::abs(diffX) > 10.f)
  {
    dir.x = (diffX > 0) ? 1.f : -1.f;
  }

  return dir;
}

sf::Vector2f SmartEnemy::getSmartNextDir(const sf::Vector2f& start, const sf::Vector2f& target) const
{
  if (!getBoard())
    return { 0,0 };

  if (!getBoard()->isHaveBoard() || getBoard()->isBoardEmpty())
    return { 0,0 };

  const sf::Vector2i startG = getBoard()->worldToGrid(start);
  const sf::Vector2i targetG = getBoard()->worldToGrid(target);
  const sf::Vector2u boardSize = getBoard()->getSizeBoard();

  auto visit = std::vector<std::vector<bool>>(boardSize.y, std::vector<bool>(boardSize.x, false));
  auto parents = std::vector<std::vector<sf::Vector2i>>(boardSize.y, std::vector<sf::Vector2i>(boardSize.x, { 0,0 }));
  auto queue = std::queue<sf::Vector2i>();
  const unsigned int sizeMove = 4;
  Action moveArr[sizeMove] = { Action::MOVE_DOWN,Action::MOVE_UP,Action::MOVE_LEFT,Action::MOVE_RIGHT };
  bool foundTarget = false;

  queue.push(startG);
  visit[startG.y][startG.x] = true;

  int visitedCount = 0;

  while (!queue.empty())
  {
    auto parent = queue.front();
    queue.pop();

    if (parent == targetG)
    {
      foundTarget = true;
      break;
    }


    ObjectSymbol currObj = getBoard()->getSymbolAt(parent);

    ObjectSymbol belowObj = ObjectSymbol::NONE;
    sf::Vector2i posBelow = parent + sf::Vector2i(0, 1);

    if (getBoard()->isValidIndex(posBelow)) {
      belowObj = getBoard()->getSymbolAt(posBelow);
    }

    bool isClimbable = (currObj == ObjectSymbol::LADDER);

    bool isHanging = (currObj == ObjectSymbol::LADDER ||
      currObj == ObjectSymbol::ROPE);

    bool hasSolidGround = (belowObj == ObjectSymbol::WALL ||
      belowObj == ObjectSymbol::GROUND ||
      belowObj == ObjectSymbol::LADDER);

    for (int i = 0; i < sizeMove; i++)
    {
      sf::Vector2i direction = mapAction(moveArr[i]);
      sf::Vector2i neighbor = parent + direction;
      sf::Vector2i belowNeighbor = neighbor + sf::Vector2i(0, 1);


      if (!getBoard()->isValidIndex(neighbor))
        continue;
      if (visit[neighbor.y][neighbor.x])
        continue;

      ObjectSymbol targetObj = getBoard()->getSymbolAt(neighbor);

      if (targetObj == ObjectSymbol::WALL)
        continue;

      if (currObj == ObjectSymbol::ROPE)
      {
        if (direction.y != 0)
          continue;
      }

      bool isPhysical = (targetObj == ObjectSymbol::LADDER || targetObj == ObjectSymbol::ROPE);

      bool isSupportedAir = false;
      if (!isPhysical)
      {
        if (getBoard()->isValidIndex(belowNeighbor))
        {
          ObjectSymbol floorObj = getBoard()->getSymbolAt(belowNeighbor);
          if (floorObj == ObjectSymbol::WALL ||
            floorObj == ObjectSymbol::LADDER ||
            floorObj == ObjectSymbol::GROUND)
          {
            isSupportedAir = true;
          }
        }
      }

      if (isPhysical || isSupportedAir)
      {
        if (direction.y == -1 && !isClimbable)
          continue;

        queue.push(neighbor);
        visit[neighbor.y][neighbor.x] = true;
        parents[neighbor.y][neighbor.x] = parent;
        visitedCount++;
      }
    }
  }


  bool debugMode = false;

  if (debugMode)
  {
    std::cout << "\n\n--- BFS REPORT (Frame) ---\n";
    std::cout << "Start: " << startG.x << "," << startG.y
      << " | Target: " << targetG.x << "," << targetG.y
      << " | Scanned: " << visitedCount << " tiles\n";

    for (size_t y = 0; y < boardSize.y; ++y)
    {
      for (size_t x = 0; x < boardSize.x; ++x)
      {
        sf::Vector2i currentPos = { (int)x, (int)y };

        if (currentPos == startG)
          std::cout << "S ";
        else if (currentPos == targetG)
          std::cout << "P ";
        else if (getBoard()->isWall(currentPos))
          std::cout << "# ";
        else if (visit[y][x])
          std::cout << ". ";
        else
          std::cout << "  ";
      }
      std::cout << "\n";
    }
    std::cout << "--------------------------\n";
  }

  if (!foundTarget)
    return { 0,0 };

  auto stepToo = targetG;

  while (parents[stepToo.y][stepToo.x] != startG)
    stepToo = parents[stepToo.y][stepToo.x];

  sf::Vector2i gridDir = stepToo - startG;
  sf::Vector2f desiredDir = static_cast<sf::Vector2f>(gridDir);

  sf::Vector2f myCenter = getBoundRec().getCenter();

  if (gridDir.y != 0)
  {
    float destCenterX = (stepToo.x * UiConfig::TILE_SIZE) + (UiConfig::TILE_SIZE / 2.f);

    if (std::abs(destCenterX - myCenter.x) > 5.0f)
    {
      if (destCenterX > myCenter.x)
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_RIGHT));
      else
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_LEFT));
    }
  }

  else if (gridDir.x != 0)
  {
    float destCenterY = (stepToo.y * UiConfig::TILE_SIZE) + (UiConfig::TILE_SIZE / 2.f);

    if (std::abs(destCenterY - myCenter.y) > 5.0f)
    {
      ObjectSymbol mySymbol = getBoard()->getSymbolAt(startG);
      bool canClimb = (mySymbol == ObjectSymbol::LADDER || mySymbol == ObjectSymbol::ROPE);

      if (destCenterY > myCenter.y && canClimb)
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_DOWN));
      else
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_UP));
    }
  }

  return desiredDir;
}

