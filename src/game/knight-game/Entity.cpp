#include "game/knight-game/Entity.hpp"

#include <iostream>
#include <HardwareSerial.h>

Entity::Entity(Vector2D& position, Vector2D velocity) 
: position(position),
  velocity(velocity)
{

}

void Entity::update(float deltaTime) 
{
    getPosition().add(velocity.copy().multiply(deltaTime));
}

Vector2D& Entity::getPosition() 
{
    return position;
}

Vector2D& Entity::getVelocity() 
{
    return velocity;
}