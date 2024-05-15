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

void Knight::update(float deltaTime) {
    TFT_eSPI& display = DisplayManager::getDisplay();
    Vector2D& velocity = getVelocity();
    Hitbox& hitbox = getHitbox();
    KnightGame* knightGame = KnightGame::getInstance();

    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(0.7);
        jumpRequest = false;
    }

    if (runRightRequest) {
        velocity.setX(0.2);
    } else if (runLeftRequest) {
        velocity.setX(-0.2);
    } else {
        velocity.setX(0);
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);

    if (deltaVelocity.getY() > 0) {
        display.fillRect(getPosition().getIntX(), ceil(getPosition().getY()) - 1, 54, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(getPosition().getIntX(), ceil(getPosition().getY() + 64 + deltaVelocity.getIntY()) - 1, 54, ceil(-deltaVelocity.getY()), TFT_BLACK);
    }

    display.fillRect(ceil(getPosition().getIntX()), getPosition().getIntY(), ceil(deltaVelocity.getX()), 64, TFT_BLACK);

    getPosition().addX(deltaVelocity.getX());

    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_X);

    if (deltaVelocity.getX() > 0 && overlapX != 0) {
        getPosition().subtractX(overlapX);
        velocity.setX(0);
    } else if (deltaVelocity.getX() < 0 && overlapX != 0) {
        getPosition().addX(overlapX);
        velocity.setX(0);
    }

    getPosition().addY(deltaVelocity.getY());

    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_Y);

    if (deltaVelocity.getY() > 0 && overlapY != 0) {
        getPosition().subtractY(overlapY);
        velocity.setY(0);
        onGround = true;
    } else if (deltaVelocity.getY() < 0 && overlapY != 0) {
        getPosition().addY(overlapY);
        velocity.setY(0);
    } else {
        onGround = false;
    }

    knightSprite.pushSprite(getPosition().getIntX(), getPosition().getIntY());
}

void Knight::jump() 
{
    if (onGround) {
        jumpRequest = true;
    }
}

void Knight::runLeft() 
{
    runLeftRequest = true;
}

void Knight::runRight() 
{
    runRightRequest = true;
}

void Knight::stopRunLeft() 
{
    runLeftRequest = false;
}

void Knight::stopRunRight() 
{
    runRightRequest = false;
}

Hitbox& Knight::getHitbox() 
{
    return hitbox;
}