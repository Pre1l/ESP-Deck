#include "game/knight-game/rectangle/ProxyHitbox.hpp"

ProxyHitbox::ProxyHitbox(std::shared_ptr<Vector2D> position, float width, float height, float offsetX) 
: Hitbox(position, width, height)
{
    this->offsetX = offsetX;
}

std::shared_ptr<Vector2D> ProxyHitbox::getPosition() 
{
    std::shared_ptr<Vector2D> position = std::make_shared<Vector2D>(*Hitbox::getPosition());
    position->addX(offsetX);
    return position;
}