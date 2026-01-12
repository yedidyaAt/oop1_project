#include <SFML/System/Vector2.hpp>
#include "Level.h"
#include "DumbEnemy.h"
#include "SmartEnemy.h"
#include "StaticObject.h"
#include "IGameEvents.h"
#include <iostream> // בשביל הדיבאג
#include "GameBar.h"


Level::Level(IGameEvents* eventsHandler):m_eventsHandler(eventsHandler){}

void Level::run( sf::Clock& clock) 
{
  float dt = clock.restart().asSeconds();
  updateObject(dt);
  handlColisions();
}

sf::Vector2f Level::getPlayerPos() const
{
  for (const auto& object : m_entities)
  {
    if (object->getSymbol() == ObjectSymbol::PLAYER)
      return object->getPos();
  }

  return { -1,-1 }; // avoid warning
}

void Level::setLevel(std::vector<std::string> board)
{
  // reset 
  m_entities.clear();

  for (int row = 0; row < board.size(); ++row)
  {
    for (int col = 0; col < board[row].size(); ++col)
    {
      char& tile = board[row][col]; 
      sf::Vector2f pos(static_cast<float>(col)*UiConfig::TILE_SIZE, static_cast<float>(row)*UiConfig::TILE_SIZE);

      if (createEntity(tile, pos)) {
        tile = ' '; 
      }
    }
  }

  m_board.loadFromData(board);

  sortByLayer();
}

bool Level::createEntity(char tile,const sf::Vector2f& pos)
{
  switch (static_cast<ObjectSymbol>(tile))
  {
  case ObjectSymbol::PLAYER:
    m_entities.push_back(std::make_unique<Player>(pos));
    return true;

  case ObjectSymbol::ENEMY:
    m_entities.push_back(std::make_unique<DumbEnemy>(pos));
    return true;

  case ObjectSymbol::COIN:
    m_coinCnt++;
    m_entities.push_back(std::make_unique<StaticObject>(pos, ObjectSymbol::COIN));
    return true;

  default:
    return false; 
  }
}

void Level::updateObject(float deltaTime)
{
  for (auto& object : m_entities)
    object->update(*this, deltaTime);
}

void Level::handlColisions()
{
  auto player = getPlayer();

  for (auto& obj : m_entities)
  {
    if (player->haveColision(*obj.get()))
    {
      processCollision(player, obj.get());
    }
  }
}

void Level::processCollision(Player* player,Object* obj)
{
  ObjectSymbol objSymbol = obj->getSymbol();

  switch (objSymbol)
  {
  case ObjectSymbol::ENEMY:
    handlPlayerVsEnemy();
    break;
  case ObjectSymbol::COIN:
    handlPlayerVsCoin(obj);
    break;
  default:
    break;
  }
}

void Level::resetPositions()
{
  for (auto& object : m_entities)
    object->resetStartPos();
}

void Level::sortByLayer() 
{
  std::sort(m_entities.begin(), m_entities.end(),
    [](const std::unique_ptr<Object>& a, const std::unique_ptr<Object>& b) 
    { 
      return a->getLayer() < b->getLayer();
    });
}

void Level::handlPlayerVsEnemy()
{
  if (m_eventsHandler) {
    m_eventsHandler->onPlayerDied();
  }
}

void Level::handlPlayerVsCoin(Object* obj)
{
  obj->destroy();
  takeCoin();

  if (m_eventsHandler) 
    m_eventsHandler->onCoinCollected();
}

Player* Level::getPlayer() const
{
  for (const auto& obj : m_entities)
    if (obj->getSymbol() == ObjectSymbol::PLAYER)
      return static_cast<Player*>(obj.get());

  return nullptr;
}

bool Level::isOnLadder(const sf::FloatRect& rect) const {
  // בודק מרכז המלבן (כי סולם צריך להיות מתחת למרכז השחקן)
  sf::Vector2f center(rect.position.x + rect.size.x/ 2.f,
                      rect.position.y + rect.size.y / 2.f);
  return m_board.getSymbolAt(center) == ObjectSymbol::LADDER;
}

void Level::takeCoin()
{
  m_coinCnt--;
}


int Level::coinLeft() const
{
  return m_coinCnt;
}

bool Level::hasFloorBelow(const sf::FloatRect& rect) const {
  // יוצר מלבן מתחת (משנה y ב-1 פיקסל), בודק אם solid
  sf::FloatRect below = rect;
  below.position.y += 1.f; // בדוק קצת מתחת
  return m_board.isHitSolid(below);
}

const Board& Level::getBoard()const
{
  return m_board;
}

const std::vector<std::unique_ptr<Object>>& Level::getObject() const
{
  return m_entities;
}

float Level::getRows() const
{
  return m_board.getSizeBoard().y;
}

float Level::getCols() const
{
  return m_board.getSizeBoard().x;
}

bool Level::isValidState(const sf::FloatRect& rect) const
{
  float tileSize = (float)UiConfig::TILE_SIZE;

  // 1. הגנה קריטית: גבולות העולם (World Bounds)
  // אם השחקן מנסה לצאת מהמסך - חסום אותו מיד.
  float worldWidth = m_board.getBoardObjects()[0].size() * tileSize;
  float worldHeight = m_board.getBoardObjects().size() * tileSize;

  if (rect.position.x < 0 || rect.position.y < 0) return false;
  if (rect.position.x + rect.size.x > worldWidth) return false;
  if (rect.position.y + rect.size.y > worldHeight) return false;

  // 2. הקטנה קטנה (Epsilon) לבדיקת תוכן
  float epsilon = 1.0f;
  sf::FloatRect checkRect = rect;
  checkRect.position.x += epsilon;
  checkRect.position.y += epsilon;
  checkRect.size.x -= 2 * epsilon;
  checkRect.size.y -= 2 * epsilon;

  int startX = (int)(checkRect.position.x / tileSize);
  int endX = (int)((checkRect.position.x + checkRect.size.x) / tileSize);
  int startY = (int)(checkRect.position.y / tileSize);
  int endY = (int)((checkRect.position.y + checkRect.size.y) / tileSize);

  // הגנה נוספת לאינדקסים (למקרה שהחישוב למעלה פספס)
  int maxRows = m_board.getBoardObjects().size();
  int maxCols = m_board.getBoardObjects()[0].size();

  for (int y = startY; y <= endY; ++y) {
    for (int x = startX; x <= endX; ++x) {

      if (y < 0 || y >= maxRows || x < 0 || x >= maxCols) return false;

      sf::FloatRect tileRect(
        sf::Vector2f(x * tileSize, y * tileSize),
        sf::Vector2f(tileSize, tileSize)
      );

      if (!checkRect.findIntersection(tileRect)) continue;

      sf::Vector2f center(tileRect.position.x + tileSize / 2.f, tileRect.position.y + tileSize / 2.f);
      ObjectSymbol sym = m_board.getSymbolAt(center);

      if (sym == ObjectSymbol::WALL || sym == ObjectSymbol::GROUND) return false;
    }
  }
  return true;
}

sf::Vector2f Level::calculateShift(const sf::FloatRect& failedRect, const sf::Vector2f& stepDir) const
{
  float tileSize = (float)UiConfig::TILE_SIZE;

  // SFML 3.0: חישוב מרכז
  sf::Vector2f centerPos = failedRect.position + (failedRect.size / 2.0f);

  // חישוב מרכז האריח הכי קרוב
  float tileCenterX = std::floor(centerPos.x / tileSize) * tileSize + (tileSize / 2.0f);
  // float tileCenterY = std::floor(centerPos.y / tileSize) * tileSize + (tileSize / 2.0f); // לא בשימוש כרגע

  sf::Vector2f fixedPos = failedRect.position; // מתחילים ממה שנכשל

  // --- מקרה 1: היצמדות לקיר (Wall Snap) ---
  if (stepDir.x != 0) {
    if (stepDir.x > 0) { // זזנו ימינה
      float wallLeftEdge = std::floor((failedRect.position.x + failedRect.size.x) / tileSize) * tileSize;
      fixedPos.x = wallLeftEdge - failedRect.size.x - 0.1f; // קצת לפני הקיר
    }
    else { // זזנו שמאלה
      float wallRightEdge = std::floor(failedRect.position.x / tileSize) * tileSize + tileSize;
      fixedPos.x = wallRightEdge + 0.1f; // קצת אחרי הקיר
    }
    return fixedPos;
  }

  // --- מקרה 2+3: סולמות ופינות (Alignment) ---
  if (stepDir.y != 0) {
    // האם אנחנו קרובים למרכז ה-X? (עד 25% סטייה)
    float diffX = tileCenterX - centerPos.x;
    float tolerance = tileSize * 0.25f;

    if (std::abs(diffX) < tolerance) {
      // שיפט! מיישרים את ה-X למרכז
      fixedPos.x = tileCenterX - (failedRect.size.x / 2.0f);
      return fixedPos;
    }
  }

  return failedRect.position; // מחזירים את המקור (כישלון)
}

sf::Vector2f Level::getMoveTo(const sf::FloatRect& curRect, const sf::Vector2f& totalVelocity, float deltaTime) const
{
  // משתנה עבודה שמתעדכן צעד אחרי צעד
  sf::Vector2f currentPos = curRect.position;

  // 1. הגנה מפני קפיצות זמן (Lag Spike Protection)
  // אם המשחק נתקע, אל תתן לשחקן לזוז 1000 פיקסלים. הגבל את הצעד.
  if (deltaTime > 0.1f) deltaTime = 0.1f;

  // פירוק לצעדים קטנים (Sub-Stepping)
  // נניח מקסימום 5 פיקסלים לצעד
  float dist = std::sqrt(totalVelocity.x * totalVelocity.x + totalVelocity.y * totalVelocity.y);
  int steps = 1;
  if (dist > 0.1f) {
    steps = std::ceil(dist / 5.0f);
  }

  sf::Vector2f stepVel = totalVelocity / (float)steps;

  for (int i = 0; i < steps; ++i)
  {
    // --- טיפול בציר X ---
    float nextX = currentPos.x + stepVel.x;
    sf::FloatRect rectX(sf::Vector2f(nextX, currentPos.y), curRect.size);

    if (isValidState(rectX)) {
      currentPos.x = nextX; // תקין, מתקדמים
    }
    else {
      // התנגשות ב-X! מנסים שיפט (הצמדה לקיר)
      sf::Vector2f shiftX = calculateShift(rectX, sf::Vector2f(stepVel.x, 0));
      // אם השיפט מחזיר מיקום שונה מהמקור - סימן שהצלחנו לתקן
      if (shiftX.x != rectX.position.x) {
        currentPos.x = shiftX.x;
      }
      // אחרת: נתקענו בקיר, ה-X נשאר במקום (currentPos.x לא משתנה)
    }

    // --- טיפול בציר Y ---
    float nextY = currentPos.y + stepVel.y; // משתמשים ב-X החדש (שאולי זז ואולי לא)
    sf::FloatRect rectY(sf::Vector2f(currentPos.x, nextY), curRect.size);

    if (isValidState(rectY)) {
      currentPos.y = nextY; // תקין, מתקדמים
    }
    else {
      // התנגשות ב-Y! מנסים שיפט (יישור לסולם)
      sf::Vector2f shiftY = calculateShift(rectY, sf::Vector2f(0, stepVel.y));

      if (shiftY.x != rectY.position.x) {
        // שימו לב: שיפט של סולם מתקן את ה-X, לא את ה-Y!
        // אז אנחנו מעדכנים את ה-X לפי התיקון
        currentPos.x = shiftY.x;

        // ובודקים שוב: האם במיקום המיושר מותר לזוז ב-Y?
        sf::FloatRect rectRetry(sf::Vector2f(currentPos.x, nextY), curRect.size);
        if (isValidState(rectRetry)) {
          currentPos.y = nextY;
        }
      }
      // אחרת: נתקענו, ה-Y נשאר במקום
    }
  }

  return currentPos;
}