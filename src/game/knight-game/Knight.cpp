#include "game/knight-game/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"

Knight::Knight(Vector2D& position) 
: Entity(position, Vector2D(0, 0.01)),
  hitbox(getPosition(), 54, 64)
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.pushImage(0, 0, 216, 64, knightIdleBitmap);
}

void Knight::update(float deltaTime) 
{
    DisplayManager::getDisplay().fillRect(getPosition().getIntX(), getPosition().getIntY(), 54, 64, TFT_BLACK);
    Entity::update(deltaTime);
    knightSprite.pushSprite(getPosition().getIntX(), getPosition().getIntY());
}

Hitbox& Knight::getHitbox() 
{
    return hitbox;
}