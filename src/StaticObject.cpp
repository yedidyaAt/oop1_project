#include "StaticObject.h"

StaticObject::StaticObject(const sf::Vector2f& position, Symbol symbol, bool isActive)
          :Object(position,symbol, isActive){}

void StaticObject::update(const Level& world, float deltaTime)
{
}
