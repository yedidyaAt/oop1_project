#pragma once
#include <functional>
#include <map>
#include <memory>
#include <SFML/System/Vector2.hpp>

#include "ObjectSymbol.h"
#include "LevelData.h"

class Object;

using CreatorFunc = std::function<std::unique_ptr<Object>(const sf::Vector2f& pos,const LevelData& data)>;

class Factory
{
public:
  static Factory& instance();
  
  std::unique_ptr<Object> creator(ObjectSymbol symbol, const sf::Vector2f& pos, const LevelData& data);

  bool registerType(ObjectSymbol symbol, CreatorFunc func);
  
  int getCreatedCnt(ObjectSymbol symbol);
  void resetCounts();
private:
  std::map<ObjectSymbol, CreatorFunc>& getMap();
  std::map<ObjectSymbol, int>& getCntMap();
  
  Factory() = default;
  Factory(Factory&) = delete;
  void operator=(const Factory&) = delete;
};
