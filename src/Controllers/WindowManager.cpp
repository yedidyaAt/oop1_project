#include "WindowManager.h"
#include "Level.h"

#include "WindowConfig.h"
#include "UiConfig.h"

WindowManager::WindowManager()
  : sf::RenderWindow(sf::VideoMode({ WindowConfig::WIDTH, WindowConfig::HEIGHT }),
    WindowConfig::TITLE)
{
  setFramerateLimit(WindowConfig::FRAME_LIMIT);
}

void WindowManager::updateGameView(const Level& level, const sf::Event::Resized* resized)
{
  setViewFromSize(resized);
  updateGameView(level);
}

void WindowManager::setViewFromSize(const sf::Event::Resized* resized)
{
  sf::FloatRect visibleArea({ 0, 0 }, { (float)resized->size.x, (float)resized->size.y });
  setView(sf::View(visibleArea));
}

void WindowManager::updateGameView(const Level& level)
{
  // יחס החלוקה: 90% למשחק, 10% לבר.
  // זה אומר שהיחס ביניהם הוא 1 ל-9.
  const float GAME_SPLIT = 0.9f;
  // const float BAR_SPLIT = 0.1f; // לא נשתמש בזה ישירות, אלא נגזור את זה מהמשחק

  // 1. חישוב גודל העולם
  float worldWidth = level.getCols() * (float)UiConfig::TILE_SIZE;
  float worldHeight = level.getRows() * (float)UiConfig::TILE_SIZE;

  // 2. יצירת מצלמת המשחק
  m_gameView = sf::View(sf::FloatRect({ 0.f, 0.f }, { worldWidth, worldHeight }));

  // 3. יצירת מצלמת הבר (לוגיקה טהורה - בלי מספרים קבועים!)
  // הרוחב זהה לרוחב העולם.
  // הגובה הוא תשיעית מגובה העולם (כדי לשמור על יחס 1:9 כמו במסך).
  float barLogicalHeight = worldHeight / 9.f;
  m_barView = sf::View(sf::FloatRect({ 0.f, 0.f }, { worldWidth, barLogicalHeight }));


  // --- 4. חישוב ה-Viewport למשחק ---

  // מתייחסים לגובה החלון כאילו הוא רק 90% (השטח שהוקצה למשחק)
  float effectiveWindowHeight = (float)getSize().y * GAME_SPLIT;
  float windowRatio = (float)getSize().x / effectiveWindowHeight;
  float levelRatio = worldWidth / worldHeight;

  float vpLeft = 0.f;
  float vpTop = 0.f;
  float vpWidth = 1.f;
  float vpHeight = 1.f;

  if (windowRatio > levelRatio)
  {
    // המסך רחב מדי -> נוצרים פסים שחורים בצדדים
    float scale = levelRatio / windowRatio;
    vpWidth = scale;
    vpHeight = GAME_SPLIT;
    vpLeft = (1.f - scale) / 2.f; // מרכוז אופקי
    vpTop = 0.f;
  }
  else
  {
    // המסך גבוה מדי -> נוצרים פסים שחורים למעלה/למטה (בתוך ה-90%)
    float scale = windowRatio / levelRatio;
    vpWidth = 1.f;
    vpHeight = scale * GAME_SPLIT;
    vpLeft = 0.f;
    vpTop = (GAME_SPLIT - vpHeight) / 2.f;
  }

  // הגדרת ה-Viewport של המשחק
  m_gameView.setViewport(sf::FloatRect({ vpLeft, vpTop }, { vpWidth, vpHeight }));


  // --- 5. הגדרת ה-Viewport של הבר (התיקון!) ---

  // אנחנו רוצים שהבר "יידבק" למשחק מלמטה, וישמור על אותו רוחב בדיוק.

  float barVpLeft = vpLeft;    // אותו קו התחלה בצד שמאל
  float barVpWidth = vpWidth;  // אותו רוחב בדיוק (כדי למנוע מריחה)

  // הבר מתחיל בדיוק איפה שהמשחק נגמר
  float barVpTop = vpTop + vpHeight;

  // הגובה הפיזי של הבר חייב להיות תשיעית מהגובה הפיזי של המשחק
  // (כי הגובה הלוגי הוא תשיעית מהגובה הלוגי של המשחק)
  // זה מבטיח 0 עיוותים!
  float barVpHeight = vpHeight / 9.f;

  m_barView.setViewport(sf::FloatRect({ barVpLeft, barVpTop }, { barVpWidth, barVpHeight }));

  // ברירת מחדל
  setView(m_gameView);
}

void WindowManager::activateGameView()
{
  setView(m_gameView);
}

void WindowManager::activateBarView()
{
  setView(m_barView);
}

sf::Vector2f WindowManager::getSizeBar() const
{
  return m_barView.getSize();
}
