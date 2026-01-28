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


void MovingObject::move(float deltaTime)
{
  deltaTime = std::min(deltaTime, 0.1f); // 0.1 max time per fram case computer stuck 


  sf::Vector2f newDir = getDirection();
  sf::Vector2f newVelocity;
  newVelocity.x = calculateXVelocity(newDir);
  newVelocity.y = calculateYVelocity(newDir,deltaTime);

  setVelocity(newVelocity);

  updateFacingDirection(newDir);
  setPosByVelocity(newVelocity,deltaTime);

  resetFrameFlags();
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
void MovingObject::onRope()
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
  if (dir.x != 0 || dir.y != 0) {
  m_lastDir = dir;
  }
}

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
  auto myBounds = getBoundRec();
  auto targetBounds = target.getBoundRec();

   //x for ladders y for ropes
  float myPosVal = isXAxis ? myBounds.position.x : myBounds.position.y;
  float mySizeVal = isXAxis ? myBounds.size.x : myBounds.size.y;

  float targetPosVal = isXAxis ? targetBounds.position.x : targetBounds.position.y;
  float targetSizeVal = isXAxis ? targetBounds.size.x : targetBounds.size.y;

  float myCenter = myPosVal + mySizeVal / 2.0f;
  float targetCenter = targetPosVal + targetSizeVal / 2.0f;
  float distance = std::abs(myCenter - targetCenter);

 
  float entryThreshold = UiConfig::TILE_SIZE * PhysicsConfig::SNAP_CORNER_THRESHOLD;

  // נכנסים רק אם המרחק סביר וגם התנאי החיצוני (מקשים/מהירות) מתקיים
  if (entryCondition && distance < entryThreshold)
  {
    float newCoord = targetCenter - (mySizeVal / 2.0f);

    if (isXAxis) 
      setPos({ newCoord, getPos().y });
    else         
      setPos({ getPos().x, newCoord });

    return true; 
  }

  return false; 
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

Board* MovingObject::getBoard() const
{
    return m_board;
}

void MovingObject::updateFacingDirection(const sf::Vector2f& dir)
{
  setLastDir(dir);
}

void MovingObject::setPosByVelocity(const sf::Vector2f& v, const float& dt)
{
  setPos(getPos() + v * dt);
}

float MovingObject::calculateXVelocity(const sf::Vector2f& dir) const
{
  return dir.x * PhysicsConfig::SPEED;
}

float MovingObject::calculateYVelocity(const sf::Vector2f& dir,float deltaTime)
{
  if (isOnLadder())
  {
    return dir.y * PhysicsConfig::SPEED;
  }

  if (isOnRope())
  {
    offFalling();
    return 0.0f; 
  }

  if (isOnGround())
  {
    checkSmashed();
    return 0.0f;
  }

  // probebly we are falling
  float newY = getVelocity().y + PhysicsConfig::GRAVITY * deltaTime;
  checkFalling(newY);
  return newY;
}

void MovingObject::onFalling()
{
  m_faling = true;
}

void MovingObject::offFalling()
{
  m_faling = false;
}

void MovingObject::resetFrameFlags()
{
  offGround();
  setOnLadder(false);
  offRope();
}

void MovingObject::resetVelocity()
{
  setVelocity({ 0.f,0.f });
}

void MovingObject::resetAllFlags()
{
  m_faling = false;         
  m_smashed = false;        
  resetFrameFlags();
}

bool MovingObject::slipperinessTester(const Object& obj)
{
  auto pBounds = getBoundRec();
  auto oBounds = obj.getBoundRec();
  auto overlap = pBounds.findIntersection(oBounds);

  if (!overlap)
    return false;

  // --- Corner Correction (החלקה למנהרה) ---
  // אם ההתנגשות היא "קיר" (X < Y) אבל החפיפה האנכית קטנה מאוד
  float cornerTolerance = UiConfig::TILE_SIZE * PhysicsConfig::SNAP_CORNER_THRESHOLD;
  float edgeTolerance = UiConfig::TILE_SIZE * PhysicsConfig::SNAP_EDGE_THRESHOLD;


  if (overlap->size.x < overlap->size.y)// coming from sides
  {
    if (overlap->size.y < cornerTolerance) // if the overlap on y is litle like stuck whit the head
    {
      if (pBounds.position.y < oBounds.position.y) //if i colision with the bottom head
        setPos({ getPos().x, getPos().y - overlap->size.y }); // החלקה למעלה
      else
        setPos({ getPos().x, getPos().y + overlap->size.y }); // החלקה למטה

      return true;
    }
  }
  else if (overlap->size.x > overlap->size.y) // התנגשות מלמעלה/למטה (רצפה/תקרה)
  {
    // בדיקת "פינה" - אם אני עומד על הרצפה אבל רק על חתיכה קטנה ממנה (פחות מה-tolerance)
    if (overlap->size.x < edgeTolerance)
    {
      // אם אני נמצא מעל הבלוק (כלומר זו רצפה, לא תקרה)
      if (pBounds.position.y < oBounds.position.y)
      {
        // giv the phisic to controle
        return true;
      }
    }
  }

  return false;
}

void MovingObject::overlapExtractor(const Object& obj)
{
  auto pBounds = getBoundRec();
  auto oBounds = obj.getBoundRec();
  auto overlap = pBounds.findIntersection(oBounds);

  if (!overlap)
    return;

  float pCenterX = pBounds.getCenter().x;
  float oCenterX = oBounds.getCenter().x;
  float pCenterY = pBounds.getCenter().y;
  float oCenterY = oBounds.getCenter().y;


  if (overlap->size.x < overlap->size.y)// coming from sides
  {
    if (pCenterX < oCenterX) // if i came from side right 
      setPos({ getPos().x - overlap->size.x, getPos().y }); //move left and sitck to him
    else
      setPos({ getPos().x + overlap->size.x, getPos().y }); //move right and sitck to him

  }
  else // coming from up or down
  {
    if (pCenterY < oCenterY) // if i cam from top to down
    {
      setPos({ getPos().x, getPos().y - overlap->size.y }); // goin up
      onGround();
    }
    else // if i cam from down to top
    {
      setPos({ getPos().x, getPos().y + overlap->size.y }); // goin down

      sf::Vector2f v = getVelocity();
      v.y = 0;
      setVelocity(v);
    }
  }
}

void MovingObject::setBoradPtr(Board& board)
{
  m_board = &board;
}

void MovingObject::reset()
{
  resetVelocity();
  resetAllFlags();
  resetStartPos();
  livenUp();
}

void MovingObject::handleLadderLogic(const Object& ladder)
{
  // don't magnet if is passing near the ladder
  if (getLastDir().x != 0)
    return;

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
  bool stable = getVelocity().y == 0;

   //קריאה לפונקציה המתמטית על ציר Y
  if (alignToCenter(rope, false,stable))
  {
    onRope();
  }
}

void MovingObject::resolveOverlap(Object& obj)
{
  if (!slipperinessTester(obj))
    overlapExtractor(obj);
}