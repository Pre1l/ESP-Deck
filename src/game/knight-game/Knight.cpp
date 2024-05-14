#include "game/knight-game/Knight.hpp"

#include "bitmap/knight-game/KnightIdleBitmap.hpp"
#include <game/knight-game/KnightGame.hpp>

Knight::Knight(Vector2D position) 
: Entity(position, Vector2D(0, 0)),
  hitbox(&getPosition(), 54, 64)
{
    knightSprite.createSprite(54, 64);
    knightSprite.setSwapBytes(true);
    knightSprite.pushImage(0, 0, 216, 64, knightIdleBitmap);
}

void Knight::update(float deltaTime) 
{
    DisplayManager::getDisplay().fillRect(getPosition().getIntX(), getPosition().getIntY(), 54, 64, TFT_BLACK);

    Vector2D deltaVelocity = getVelocity().copy().multiply(deltaTime);

    getHitbox().getPosition()->add(deltaVelocity);
    if (KnightGame::getInstance()->calculateCollisions(getHitbox())) {
        getHitbox().getPosition()->subtract(deltaVelocity);
    }

    knightSprite.pushSprite(getPosition().getIntX(), getPosition().getIntY());
}

Hitbox& Knight::getHitbox() 
{
    return hitbox;
}