#include "MovingObject.h"
#include <iostream>
#include <cmath> 


MovingObject::MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive)
  :Object(position, symbol, isActive)
{
}

Layer MovingObject::getLayer()
{
    return Layer::DYNAMICS;
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
  currentVel.x = dir.x * GameConfig::Physics::SPEED;

  // 3. חישוב Y (שימוש בפונקציות בלבד!)
  if (isOnLadder())
  {
    currentVel.y = dir.y * GameConfig::Physics::SPEED;
  }
  else if (isOnRope())
  {
    currentVel.y = 0;
  }
  else
  {
    // כבידה
    if (!isOnGround()) {
      currentVel.y += GameConfig::Physics::GRAVITY * deltaTime;
      
 /*     std::cout << getVelocity().x << std::endl;
      if (getVelocity().y > UiConfig::TILE_SIZE)
        SoundManager::instance().playSound(SoundType::FALL);*/

    }
    else {
      currentVel.y = 0;
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
  float entryThreshold = UiConfig::TILE_SIZE * GameConfig::Physics::LADDER_SNAP_THRESHOLD;
  // טווח "הידבקות" צר (כדי להשאיר את השחקן תפוס אם הוא כבר שם)
  float stickThreshold = 2.0f;

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
  float cornerTolerance = UiConfig::TILE_SIZE* GameConfig::Physics::LADDER_SNAP_THRESHOLD;

  if (overlap->size.x < overlap->size.y)
  {
    if (overlap->size.y < cornerTolerance)
    {
      std::cout << "i was here: " << __LINE__<< std::endl;
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