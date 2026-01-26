#pragma once
#include "Object.h"
#include "SoundManager.h"
#include "Board.h"


class MovingObject : public Object {
public:
  MovingObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive=true);

  virtual void update(float deltaTime,const LevelData* levelData) override = 0;

  virtual void handleCollision(Object& obj) override  = 0;
  void setBoradPtr(Board& board);

  virtual void reset() override;
protected:
  virtual void handleCollision(Player& obj) override = 0;
  virtual void handleCollision(Enemy& obj) override = 0;
  virtual void handleCollision(Coin& obj) override = 0;
  virtual void handleCollision(Wall& obj) override = 0;
  virtual void handleCollision(Ground& obj) override = 0;
  virtual void handleCollision(Ladder& obj) override = 0;
  virtual void handleCollision(Rope& obj) override = 0;

  //delete no needs
  sf::Vector2f getVelocity(const sf::Vector2f&, float speed, float deltaTime)const;

  sf::Vector2f getLastDir()const;

  void setVelocity(const sf::Vector2f& v);
  sf::Vector2f getVelocity() const;

  void onGround(); //reset velocity and ground
  void offGround();
  bool isOnGround() const;

  bool isOnLadder() const;
  void setOnLadder(bool flag);

  bool isOnRope() const;
  void OnRope();
  void offRope();

  virtual sf::Vector2f getDirection() = 0;
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
  sf::Vector2f m_lastDir;
  sf::Vector2f m_velocity = { 0,0 };
  bool m_onLadder = false;
  bool m_onRope = false;
  bool m_onGround = false;
  bool m_faling = false;
  bool m_smashed = false;
  Board* m_board = nullptr;
};