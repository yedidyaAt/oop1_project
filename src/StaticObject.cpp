#include "StaticObject.h"
#include "Level.h"

StaticObject::StaticObject(const sf::Vector2f& position, ObjectSymbol symbol, bool isActive)
          :Object(position,symbol, isActive){}

void StaticObject::update(const Level& world, float deltaTime)
{
}

