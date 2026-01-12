#pragma once

class IGameEvents
{
public:
  virtual ~IGameEvents() = default;

  virtual void onCoinCollected() = 0;
  virtual void onPlayerDied() = 0;
  virtual void onLevelCompleted() = 0;
  virtual void onTimeRunningOut() = 0;
};