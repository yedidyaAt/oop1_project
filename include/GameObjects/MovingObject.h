#pragma once
#include "Object.h"
#include "SoundManager.h"
#include "Board.h"


class MovingObject : public Object {
public:
  MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive=true);

  virtual void update(float deltaTime,const LevelData* levelData) override = 0;

  
  void handleCollision(Object & obj) override = 0;
  virtual void reset() override;
  void handleCollision(Player & obj) override = 0;
  void handleCollision(Enemy & obj) override = 0;
  void handleCollision(Coin & obj) override = 0;
  void handleCollision(Wall & obj) override = 0;
  void handleCollision(Ground & obj) override = 0;
  void handleCollision(Ladder & obj) override = 0;
  void handleCollision(Rope & obj) override = 0;
  
  void setBoradPtr(Board& board);
protected:
  virtual sf::Vector2f getDirection() = 0;
  sf::Vector2f getVelocity() const;
  sf::Vector2f getLastDir()const;



  void onGround(); //reset velocity and ground
  void offGround();
  void setOnLadder(bool flag);

  void onRope();
  void offRope();

  bool isOnGround() const;
  bool isOnLadder() const;
  bool isOnRope() const;

  void move(float deltaTime);
  void setLastDir(const sf::Vector2f& dir );
  bool isOnObject(const Object& obj)const;
  bool isOnObject(const Object* obj)const;

  void handleLadderLogic(const Object& ladder);
  void handleRopeLogic(const Object& rope);

  // התנגשות משודרגת עם החלקה לפינות
  void resolveOverlap(Object& obj);

  bool alignToCenter(const Object& target, bool isXAxis, bool entryCondition);

  void keepObjInsideMap();
  bool checkFallingOutsideMap();
  void checkFalling(float fallSpeed);
  void checkSmashed();

  Board* getBoard() const;
private:
  void updateFacingDirection(const sf::Vector2f& dir);
  void setPosByVelocity(const sf::Vector2f& v,const float& dt);
  void setVelocity(const sf::Vector2f& v);

  float calculateXVelocity(const sf::Vector2f& dir)const;
  float calculateYVelocity(const sf::Vector2f& dir,float deltaTime);

  void onFalling();
  void offFalling();

  void resetFrameFlags();



  sf::Vector2f m_lastDir;
  sf::Vector2f m_velocity = { 0,0 };

  // logic move
  bool m_onLadder = false;
  bool m_onRope = false;
  bool m_onGround = false;
  
  // for sounds
  bool m_faling = false;
  bool m_smashed = false;
  
  //data board
  Board* m_board = nullptr;
};