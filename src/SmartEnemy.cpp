
#include "SmartEnemy.h"

#include "Enemy.h"
#include "Player.h"
#include "Rope.h"
#include "Ladder.h"
#include "Ground.h"
#include "Coin.h"
#include "Wall.h"

#include "InputHandler.h"


SmartEnemy::SmartEnemy(const sf::Vector2f& position,bool isActive)
                      :Enemy(position, isActive){}


void SmartEnemy::update(float deltaTime)
{
  move(deltaTime);
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
  if (!m_playerTarget) return { 0, 0 };

  sf::Vector2f myPos = getPos();
  sf::Vector2f playerPos = m_playerTarget->getPos();

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

void SmartEnemy::setTarget(const Object& obj)
{
  m_playerTarget = &obj;
}





