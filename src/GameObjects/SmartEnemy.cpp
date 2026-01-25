
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

SmartEnemy::SmartEnemy(const sf::Vector2f& position,bool isActive)
                      :Enemy(position, isActive){}


void SmartEnemy::update(float deltaTime)
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
void SmartEnemy::handleCollision(Enemy& obj)
{
}
void SmartEnemy::handleCollision(Coin& obj)
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
  //return getSmartNextDir(getPos(),m_board->getPlayerPosition());
  return getHafeSmartDir();
}

sf::Vector2f SmartEnemy::getHafeSmartDir() const
{
  if (!m_board)
    return { 0, 0 };


  sf::Vector2f myPos = getPos();
  sf::Vector2f playerPos = m_board->getPlayerPosition();

  sf::Vector2f dir = { 0, 0 };

  // בדיקת הפרשים
  float diffX = playerPos.x - myPos.x;
  float diffY = playerPos.y - myPos.y;

  // עדיפות ראשונה: סולמות (אם אנחנו על סולם או צריכים לעלות/לרדת)
  if (isOnLadder())
  {
    if (std::abs(diffY) > 10.f) // אם יש הפרש גובה משמעותי
    {
      dir.y = (diffY > 0) ? 1.f : -1.f; // למטה או למעלה
      return dir;
    }
  }

  // עדיפות שנייה: ריצה ימינה/שמאלה
  if (std::abs(diffX) > 10.f) // אם אנחנו לא באותו טור
  {
    dir.x = (diffX > 0) ? 1.f : -1.f; // ימינה או שמאלה
  }

  // אם האויב תקוע מתחת לשחקן ואין לו איך לעלות, 
  // אויב ממש חכם יחפש סולם הקרוב, אבל זה כבר אלגוריתם מורכב (BFS).
  // לבינתיים - זה יגרום לו לרדוף באגרסיביות.

  return dir;
}

sf::Vector2f SmartEnemy::getSmartNextDir(const sf::Vector2f& start, const sf::Vector2f& target) const
{
  //safe check
  if (!m_board)
    return { 0,0 };

  if (!m_board->isHaveBoard() || m_board->isBoardEmpty())
    return { 0,0 };

  // set World // G = Grid
  const sf::Vector2i startG = m_board->worldToGrid(getBoundRec().getCenter());
  const sf::Vector2i targetG = m_board->worldToGrid(target);
  const sf::Vector2u boardSize = m_board->getSizeBoard();

  //struct  for BFS
  auto visit     = std::vector<std::vector<bool>>(boardSize.y, std::vector<bool>(boardSize.x,false));
  auto parents   = std::vector<std::vector<sf::Vector2i>>(boardSize.y, std::vector<sf::Vector2i>(boardSize.x,{0,0}));
  auto queue     = std::queue<sf::Vector2i>();
  const unsigned int sizeMove = 4;  // if tomarow i want diagnle move
  Action move[sizeMove] = { Action::MOVE_DOWN,Action::MOVE_UP,Action::MOVE_LEFT,Action::MOVE_RIGHT };
  bool foundTarget = false;

  // start calculation
  queue.push(startG);
  visit[startG.y][startG.x] = true;

  // debag
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

  
    ObjectSymbol currObj = m_board->getSymbolAt(parent); // איפה אני עומד כרגע

    ObjectSymbol belowObj = ObjectSymbol::NONE;
    sf::Vector2i posBelow = parent + sf::Vector2i(0, 1);

    if (m_board->isValidIndex(posBelow)) {
      belowObj = m_board->getSymbolAt(posBelow); // מה יש מתחתיי
    }

    // 2. הגדרת מצבים (Booleans) לקריאות
    bool isClimbable = (currObj == ObjectSymbol::LADDER);

    bool isHanging = (currObj == ObjectSymbol::LADDER ||
      currObj == ObjectSymbol::ROPE);

    bool hasSolidGround = (belowObj == ObjectSymbol::WALL ||
      belowObj == ObjectSymbol::GROUND ||
      belowObj == ObjectSymbol::LADDER );

    // ==========================================

   // לולאת השכנים
    for (int i = 0; i < sizeMove; i++)
    {
      sf::Vector2i direction = mapAction(move[i]);
      sf::Vector2i neighbor = parent + direction;      // השכן
      sf::Vector2i belowNeighbor = neighbor + sf::Vector2i(0, 1); // מה שמתחת לשכן

      // 1. בדיקת גבולות וביקור
      if (!m_board->isValidIndex(neighbor)) 
        continue;
      if (visit[neighbor.y][neighbor.x])
        continue;

      ObjectSymbol targetObj = m_board->getSymbolAt(neighbor);

      // קיר חוסם כניסה
      if (targetObj == ObjectSymbol::WALL) 
        continue;

      if (currObj == ObjectSymbol::ROPE)
      {
        // אם מנסים לזוז בציר ה-Y (למעלה או למטה)
        if (direction.y != 0)
          continue; // דלג, תנועה לא חוקית
      }
      // --- הבדיקה שביקשת ---

      // האם זה אובייקט פיזי? (סולם או חבל)
      bool isPhysical = (targetObj == ObjectSymbol::LADDER || targetObj == ObjectSymbol::ROPE);

      // האם זה אוויר שיש מתחתיו רצפה?
      bool isSupportedAir = false;
      if (!isPhysical) // אם זה לא פיזי, זה כנראה אוויר/מטבע
      {
        if (m_board->isValidIndex(belowNeighbor))
        {
          ObjectSymbol floorObj = m_board->getSymbolAt(belowNeighbor);
          // רצפה נחשבת: קיר, או ראש של סולם
          if (floorObj == ObjectSymbol::WALL ||
              floorObj == ObjectSymbol::LADDER ||
              floorObj == ObjectSymbol::GROUND)
          {
            isSupportedAir = true;
          }
        }
      }

      // התנאי הקובע: נכנסים רק אם זה פיזי או אוויר נתמך
      if (isPhysical || isSupportedAir)
      {
        // (חובה) הגבלה קטנה לעלייה למעלה: אי אפשר לעלות לאוויר סתם ככה, חייבים להיות על סולם כרגע
        if (direction.y == -1 && !isClimbable) 
          continue;

        queue.push(neighbor);
        visit[neighbor.y][neighbor.x] = true;
        parents[neighbor.y][neighbor.x] = parent;
        visitedCount++;
      }
    }
  }
  

  // ==========================================
//           DEBUG VISUALIZATION
// ==========================================
// שנה ל-false כשאתה מסיים לדבג כדי לא להאט את המשחק
  bool debugMode = false;

  if (debugMode)
  {
    // ניקוי מסך (חלקי) כדי שזה יראה כמו אנימציה, או פשוט הפרדה ברורה
    std::cout << "\n\n--- BFS REPORT (Frame) ---\n";
    std::cout << "Start: " << startG.x << "," << startG.y
      << " | Target: " << targetG.x << "," << targetG.y
      << " | Scanned: " << visitedCount << " tiles\n";

    for (size_t y = 0; y < boardSize.y; ++y)
    {
      for (size_t x = 0; x < boardSize.x; ++x)
      {
        // בדיוק איפה אנחנו?
        sf::Vector2i currentPos = { (int)x, (int)y };

        if (currentPos == startG)
          std::cout << "S "; // Start (Enemy)
        else if (currentPos == targetG)
          std::cout << "P "; // Player (Target)
        else if (m_board->isWall(currentPos))
          std::cout << "# "; // Wall
        else if (visit[y][x])
          std::cout << ". "; // Visited (המסלול שנבדק!)
        else
          std::cout << "  "; // לא נבדק
      }
      std::cout << "\n";
    }
    std::cout << "--------------------------\n";
  }
  // ==========================================

  if (!foundTarget)
    return { 0,0 };

  // goin back by ask who he is father to start
  auto stepToo = targetG;

  while (parents[stepToo.y][stepToo.x] != startG)
    stepToo = parents[stepToo.y][stepToo.x];

  // ============================================================
      // הלוגיקה שלך: בדיקת יישור לפי stepToo
      // ============================================================

      // לאן ה-BFS רוצה ללכת?
  sf::Vector2i gridDir = stepToo - startG;
  sf::Vector2f desiredDir = static_cast<sf::Vector2f>(gridDir);

  // המיקום הנוכחי שלי בפיקסלים
  sf::Vector2f myCenter = getBoundRec().getCenter();

  // --- מקרה 1: ה-BFS רוצה תנועה אנכית (סולם) ---
  if (gridDir.y != 0)
  {
    // חישוב מרכז העמודה של המשבצת *אליה* אנחנו הולכים (stepToo)
    float destCenterX = (stepToo.x * UiConfig::TILE_SIZE) + (UiConfig::TILE_SIZE / 2.f);

    // "מרחב סלחנות" - אם אנחנו בסטייה של יותר מ-5 פיקסלים
    if (std::abs(destCenterX - myCenter.x) > 5.0f)
    {
      // אנחנו לא מיושרים -> דורסים את הפקודה האנכית ומחליפים באופקית
      if (destCenterX > myCenter.x)
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_RIGHT));
      else
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_LEFT));
    }

    // אם הגענו לפה, אנחנו מיושרים (בטווח ה-5 פיקסלים).
    // מחזירים את desiredDir המקורי (למעלה/למטה).
  }

  // --- מקרה 2: ה-BFS רוצה תנועה אופקית (ימינה/שמאלה) ---
  // הוספתי את זה כדי להשלים את הלוגיקה שלך גם למצב של כניסה למנהרה
  else if (gridDir.x != 0)
  {
    // חישוב מרכז השורה של המשבצת *אליה* אנחנו הולכים
    float destCenterY = (stepToo.y * UiConfig::TILE_SIZE) + (UiConfig::TILE_SIZE / 2.f);

    // בדיקת גובה - אם אנחנו לא בגובה הנכון להיכנס למנהרה
    if (std::abs(destCenterY - myCenter.y) > 5.0f)
    {
      // דורסים את הפקודה האופקית ומחליפים באנכית
      if (destCenterY > myCenter.y)
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_DOWN));
      else
        return static_cast<sf::Vector2f>(mapAction(Action::MOVE_UP));
    }
  }

  return desiredDir;
}





