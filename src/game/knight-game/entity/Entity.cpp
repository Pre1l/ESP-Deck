#include "game/knight-game/entity/Entity.hpp"

#include <iostream>
#include <HardwareSerial.h>

Entity::Entity(Vector2D& position, Vector2D velocity) 
: position(position),
  velocity(velocity)
{

}

Vector2D& Entity::getPosition() 
{
    return position;
}

Vector2D& Entity::getVelocity() 
{
    return velocity;
}