#include "MovingObject.h"
#include <iostream>
#include <cmath> 

#include "PhysicsConfig.h"
#include "UiConfig.h"
#include "SoundType.h"

MovingObject::MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive)
  :Object(position, symbol, isActive)
{
}

sf::Vector2f MovingObject::getVelocity(const sf::Vector2f& dir, float speed, float deltaTime) const
{
  return dir*speed*deltaTime;
}

void MovingObject::move(float deltaTime)
{
  if (deltaTime > 0.1f) deltaTime = 0.1f;

  // 1. מעתיקים את המהירות הנוכחית למשתנה מקומי לעבודה
  sf::Vector2f currentVel = getVelocity();
  sf::Vector2f dir = getDirection();

  // 2. חישוב X
  currentVel.x = dir.x * PhysicsConfig::SPEED;

  // 3. חישוב Y (שימוש בפונקציות בלבד!)
  if (isOnLadder())
  {
    currentVel.y = dir.y * PhysicsConfig::SPEED;
  }
  else if (isOnRope())
  {
    m_faling = false;
    currentVel.y = 0;
  }
  else
  {
    // כבידה
    if (!isOnGround()) 
      {
        currentVel.y += PhysicsConfig::GRAVITY* deltaTime;
        checkFalling(currentVel.y);
      }
    else {
      currentVel.y = 0;
      checkSmashed();
    }
  }

  // 4. עדכון המהירות בחזרה לאובייקט
  setVelocity(currentVel);

  // 5. תזוזה
  setPos(getPos() + currentVel * deltaTime);

  // 6. כיוון
  if (dir.x != 0 || dir.y != 0) {
    setLastDir(dir);
  }

  // 7. איפוס דגלים דרך פונקציות
  offGround();
  setOnLadder(false);
  offRope();
}

sf::Vector2f MovingObject::getLastDir() const
{
    return m_lastDir;
}

sf::Vector2f MovingObject::getVelocity() const
{
  return m_velocity;
}
void MovingObject::setVelocity(const sf::Vector2f & v)
{
  m_velocity = v;
}

bool MovingObject::isOnGround() const
{
  return m_onGround;
}
void MovingObject::onGround()
{
  m_onGround = true;
  m_velocity.y = 0;
}
void MovingObject::offGround()
{
  m_onGround = false;
}

bool MovingObject::isOnLadder() const
{
  return m_onLadder;
}
void MovingObject::setOnLadder(bool flag)
{
  m_onLadder = flag;
}

bool MovingObject::isOnRope() const
{
  return m_onRope;
}
void MovingObject::OnRope()
{
  m_onRope = true;
  m_velocity.y = 0;
}

void MovingObject::offRope()
{
  m_onRope = false;
}

void MovingObject::setLastDir(const sf::Vector2f& dir)
{
  m_lastDir = dir;
}

//bool MovingObject::isOnObject(const Object& obj)const
//{
//  const auto& overlap = getBoundRec().findIntersection(obj.getBoundRec());
//  
//  float isOverlapMount = UiConfig::TILE_SIZE * 0.0f;
//
// if(overlap.has_value())
//  if (overlap->size.x >= isOverlapMount)
//    return true;
//
//  return false;
//}

bool MovingObject::isOnObject(const Object& obj) const
{
  // 1. שליפת המלבנים
  sf::FloatRect myRect = getBoundRec();
  sf::FloatRect objRect = obj.getBoundRec();

  // 2. חישוב המרכזים (ב-SFML 3 יש פונקציה מובנית שעושה את זה)
  float myCenterX = myRect.getCenter().x;
  float objCenterX = objRect.getCenter().x;

  // 3. חישוב המרחק האבסולוטי בין המרכזים
  float distanceX = std::abs(myCenterX - objCenterX);

  // 4. חישוב סכום חצאי הרוחב (שים לב: width הפך ל-size.x)
  float combinedHalfWidths = (myRect.size.x / 2.0f) + (objRect.size.x / 2.0f);

  // 5. חישוב החפיפה בפועל
  float overlapX = combinedHalfWidths - distanceX;

  // 6. התנאי: לפחות 40% חפיפה
  float minOverlapRequired = UiConfig::TILE_SIZE * 0.40f;

  if (overlapX >= minOverlapRequired)
  {
    return true;
  }

  return false;
}

bool MovingObject::isOnObject(const Object* obj) const
{
  std::cout << obj << std::endl;
  if (!obj)
    return false;

  return isOnObject(*obj);
}

bool MovingObject::alignToCenter(const Object& target, bool isXAxis, bool entryCondition)
{
  // 1. שליפת גבולות
  auto myBounds = getBoundRec();
  auto targetBounds = target.getBoundRec();

  // 2. בחירת משתנים לפי הציר המבוקש (X או Y)
  // אם isXAxis אמת -> עובדים על רוחב ומיקום X (לסולמות)
  // אחרת -> עובדים על גובה ומיקום Y (לחבלים)
  float myPosVal = isXAxis ? myBounds.position.x : myBounds.position.y;
  float mySizeVal = isXAxis ? myBounds.size.x : myBounds.size.y;

  float targetPosVal = isXAxis ? targetBounds.position.x : targetBounds.position.y;
  float targetSizeVal = isXAxis ? targetBounds.size.x : targetBounds.size.y;

  // 3. חישוב מרכזים ומרחק
  float myCenter = myPosVal + mySizeVal / 2.0f;
  float targetCenter = targetPosVal + targetSizeVal / 2.0f;
  float distance = std::abs(myCenter - targetCenter);

  // 4. הגדרת ספים (Thresholds)
  // טווח כניסה רחב (20% מגודל תא)
  float entryThreshold = UiConfig::TILE_SIZE * PhysicsConfig::LADDER_SNAP_THRESHOLD;
  // טווח "הידבקות" צר (כדי להשאיר את השחקן תפוס אם הוא כבר שם)
  float stickThreshold = 20.0f;

  // --- לוגיקה 1: תחזוקה (Stickiness) ---
  // אם אנחנו כבר ממש קרובים למרכז, נשארים שם (מתעלמים מתנאי הכניסה)
   if (distance < stickThreshold)
    {
      float newCoord = targetCenter - (mySizeVal / 2.0f);

      if (isXAxis) setPos({ newCoord, getPos().y });
      else         setPos({ getPos().x, newCoord });

      return true; // בוצע שינוי
    }
  
  // --- לוגיקה 2: כניסה (Entry) ---
  // נכנסים רק אם המרחק סביר וגם התנאי החיצוני (מקשים/מהירות) מתקיים
  if (entryCondition && distance < entryThreshold)
  {
    float newCoord = targetCenter - (mySizeVal / 2.0f);

    if (isXAxis) setPos({ newCoord, getPos().y });
    else         setPos({ getPos().x, newCoord });

    return true; // בוצע שינוי
  }

  return false; // לא בוצע שינוי
}

void MovingObject::keepObjInsideMap()
{
  if (!m_board) return;

  sf::Vector2u gridDimensions = m_board->getSizeBoard();

  float mapWidth = gridDimensions.x * UiConfig::TILE_SIZE;
 

  sf::Vector2f currentPos = getPos();
  float tileSize = UiConfig::TILE_SIZE; 

  if (currentPos.x < 0)
  {
    currentPos.x = 0;
  }
  else if (currentPos.x + tileSize > mapWidth)
  {
    currentPos.x = mapWidth - tileSize;
  }

  if (currentPos.y < 0)
  {
    currentPos.y = 0;
  }

  setPos(currentPos);
}

bool MovingObject::checkFallingOutsideMap()
{
  if (!m_board)
    return false;

  sf::Vector2u boardSize = m_board->getSizeBoard();
  float tileSize = UiConfig::TILE_SIZE;
  float mapHight = boardSize.y * tileSize;
  sf::Vector2f curPos = getPos();
  
  if (curPos.y > mapHight)
  {
    destroy();
    return true;
  }

  return false;
 }

void MovingObject::checkFalling(float fallSpeed)
{
  float fallThreshold = PhysicsConfig::FALL_THRESHOLD;

  if (!m_faling && fallSpeed > fallThreshold)
  {
    m_faling = true;
    m_smashed = false;
    SoundManager::instance().playSound(SoundType::FALL);
  }
}

void MovingObject::checkSmashed()
{
  if (!m_smashed && m_faling)
  {
    m_faling = false;
    m_smashed = true;
    SoundManager::instance().playSound(SoundType::SMASHED);
  }
}

void MovingObject::setBoradPtr(Board& board)
{
  m_board = &board;
}

void MovingObject::reset()
{
  resetStartPos();
  livenUp();
}

void MovingObject::handleLadderLogic(const Object& ladder)
{
  if (getLastDir().x != 0)
    return;
  // תנאי כניסה: מנסה לעלות למעלה
  bool isTryingToClimb = (getLastDir().y != 0);

  // קריאה לפונקציה המתמטית על ציר X
  if (alignToCenter(ladder, true, isTryingToClimb))
  {
    // אם הצלחנו להתיישר -> מאפסים מהירות אופקית כדי למנוע רעידות
    sf::Vector2f v = getVelocity();
    setVelocity({ 0.f, v.y });
    
  }
}

void MovingObject::handleRopeLogic(const Object& rope)
{
  // תנאי כניסה:
  // 1. לוחץ לצדדים (dir.x != 0)
  // 2. יציב יחסית (לא נופל במהירות מטורפת)
  bool sides = getLastDir().x != 0;
  bool stable = getVelocity().y == 0;

  // קריאה לפונקציה המתמטית על ציר Y
  if (alignToCenter(rope, false, sides && stable))
  {
    // אם הצלחנו להתיישר -> מפעילים מצב חבל
    OnRope();
  }
}

void MovingObject::resolveOverlap(Object& obj)
{
  auto pBounds = getBoundRec();
  auto oBounds = obj.getBoundRec();
  auto overlap = pBounds.findIntersection(oBounds);

  if (!overlap) return;

  // --- Corner Correction (החלקה למנהרה) ---
  // אם ההתנגשות היא "קיר" (X < Y) אבל החפיפה האנכית קטנה מאוד
  float cornerTolerance = UiConfig::TILE_SIZE* PhysicsConfig::LADDER_SNAP_THRESHOLD;

  if (overlap->size.x < overlap->size.y)
  {
    if (overlap->size.y < cornerTolerance)
    {
      // החלקה: דחיפה עדינה ב-Y במקום עצירה ב-X
      if (pBounds.position.y < oBounds.position.y)
        setPos({ getPos().x, getPos().y - overlap->size.y }); // החלקה למעלה
      else
        setPos({ getPos().x, getPos().y + overlap->size.y }); // החלקה למטה

      return; // יצאנו! לא עוצרים מהירות אופקית
    }
  }

  // --- פתרון התנגשות רגיל (Standard Collision) ---

  // חישוב מרכזים ל-SFML 3
  float pCenterX = pBounds.getCenter().x;
  float oCenterX = oBounds.getCenter().x;
  float pCenterY = pBounds.getCenter().y;
  float oCenterY = oBounds.getCenter().y;

  if (overlap->size.x < overlap->size.y)
  {
    // תיקון אופקי (X) - קיר
    if (pCenterX < oCenterX)
      setPos({ getPos().x - overlap->size.x, getPos().y });
    else
      setPos({ getPos().x + overlap->size.x, getPos().y });

    // לא חובה לאפס מהירות X לשחקן, אבל אפשרי
  }
  else
  {
    // תיקון אנכי (Y) - רצפה או תקרה
    if (pCenterY < oCenterY)
    {
      // רצפה
      setPos({ getPos().x, getPos().y - overlap->size.y });
      onGround();
    }
    else
    {
      // תקרה
      setPos({ getPos().x, getPos().y + overlap->size.y });

      sf::Vector2f v = getVelocity();
      v.y = 0;
      setVelocity(v);
    }
  }
}