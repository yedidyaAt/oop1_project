#pragma once
#include <functional>
#include <map>
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Const.h"

class Object;

using CreatorFunc = std::function<std::unique_ptr<Object>(const sf::Vector2f& pos,const LevelData& data)>;

class Factory
{
public:
  static Factory& instance();
  
  std::unique_ptr<Object> creator(ObjectSymbol symbol, const sf::Vector2f& pos, const LevelData& data);

  bool registerType(ObjectSymbol symbol, CreatorFunc func);
private:
  std::map<ObjectSymbol, CreatorFunc>& getMap();
  
  Factory() = default;
  Factory(Factory&) = delete;
  void operator=(const Factory&) = delete;
};
