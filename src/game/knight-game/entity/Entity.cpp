#include "game/knight-game/entity/Entity.hpp"

#include <iostream>
#include <HardwareSerial.h>

Entity::Entity(std::shared_ptr<Vector2D> position, Hitbox hitbox) 
: position(position),
  hitbox(hitbox)
{
    
}

std::shared_ptr<Vector2D> Entity::getPosition() 
{
    return position;
}

Hitbox& Entity::getHitbox() 
{
    return hitbox;
}