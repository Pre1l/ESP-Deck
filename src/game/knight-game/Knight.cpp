#include "game/knight-game/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"

Knight::Knight(Vector2D& position) 
: Entity(position, Vector2D(0, 0), Hitbox(position, 54, 64))
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.pushImage(0, 0, 216, 64, knightIdleBitmap);
    getVelocity()->addY(1);
}

void Knight::update(float deltaTime) 
{
    Entity::update(deltaTime);
    knightSprite.pushSprite(getPosition()->getIntX(), getPosition()->getIntY());
}