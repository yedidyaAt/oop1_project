#include "Factory.h"
#include "Object.h"

Factory& Factory::instance()
{
  static Factory inc;

  return inc;
}

std::unique_ptr<Object> Factory::creator(ObjectSymbol symbol,const sf::Vector2f& pos, const LevelData& data)
{
  auto it = getMap().find(symbol);

  if (it != getMap().end())
  {
    getCntMap()[symbol]++;
    return it->second(pos, data);
  }

  return nullptr;
}

bool Factory::registerType(ObjectSymbol symbol, CreatorFunc func)
{
  getMap()[symbol] = std::move(func);
  return true;
}

int Factory::getCreatedCnt(ObjectSymbol symbol)
{
  return getCntMap()[symbol];
}

void Factory::resetCounts()
{
  getCntMap().clear();
}

std::map<ObjectSymbol, CreatorFunc>& Factory::getMap()
{
  static std::map<ObjectSymbol, CreatorFunc> map;
  return map;
}

std::map<ObjectSymbol, int>& Factory::getCntMap()
{
  static std::map<ObjectSymbol, int> map;
  return map;
}
