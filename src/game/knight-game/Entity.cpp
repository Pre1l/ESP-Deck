#include "game/knight-game/Entity.hpp"

Entity::Entity(Vector2D& position, Vector2D velocity, Hitbox hitbox) 
{
    this->position = &position;
    this->velocity = &velocity;
    this->hitbox = &hitbox;
}

void Entity::update(float deltaTime) 
{
    position->add(velocity->copy().multiply(deltaTime));
}

Vector2D* Entity::getPosition() 
{
    return position;
}

Vector2D* Entity::getVelocity() 
{
    return velocity;
}

Hitbox* Entity::getHitbox() 
{
    return hitbox;
}