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
    
    if (runLeftRequest == true && runLeftCheck == false) {
        velocity.subtractX(0.3);
        runLeftCheck = true;
    } else if (runLeftCheck == true) {
        velocity.addX(0.3);
        runLeftCheck = false;
    }

    if (runRightRequest == true && runRightCheck == false) {
        velocity.addX(0.3);
        runRightCheck = true;
    } else if (runRightCheck == true) {
        velocity.subtractX(0.3);
        runRightCheck = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);

    if (deltaVelocity.getY() > 0) {
        display.fillRect(getPosition().getIntX(), ceil(getPosition().getY()) - 1, 54, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(getPosition().getIntX(), ceil(getPosition().getY() + 64 + deltaVelocity.getIntY()) - 1, 54, ceil(-deltaVelocity.getY()), TFT_BLACK);
    }

    if (deltaVelocity.getX() > 0) {
        display.fillRect(ceil(getPosition().getIntX()), getPosition().getIntY(), ceil(deltaVelocity.getX()), 64, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(ceil(getPosition().getIntX()), getPosition().getIntY(), ceil(deltaVelocity.getX()), 64, TFT_BLACK);
    }

    getPosition().add(deltaVelocity);

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

    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_X);
    if (deltaVelocity.getX() > 0 && overlapX != 0) {
        getPosition().subtractX(overlapX);
        velocity.setY(0);
    } else if (deltaVelocity.getX() < 0 && overlapX != 0) {
        getPosition().addX(overlapX);
        velocity.setX(0);
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

/*    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(0.5);
        jumpRequest = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);

    if (runLeftRequest == true && runLeftCheck == false) {
        velocity.subtractX(0.2);
        runLeftCheck = true;
    } else if (runLeftCheck == true) {
        velocity.addX(0.2);
        runLeftCheck = false;
    }

    if (runRightRequest == true && runRightCheck == false) {
        velocity.addX(0.2);
        runRightCheck = true;
    } else if (runRightCheck == true) {
        velocity.subtractX(0.2);
        runRightCheck = false;
    }

    float overlapX;

    if (velocity.getX() > 0) {
        overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_RIGHT);
    } else if (velocity.getX() < 0) {
        overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_LEFT);
    }

    if (overlapX != 0) {
        velocity.subtractX(overlapX);
    }

    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_Y);

    if (deltaVelocity.getY() > 0 && overlapY != 0) {
        deltaVelocity.subtractY(overlapY);
        onGround = true;
    } else if (deltaVelocity.getY() < 0 && overlapY != 0) {
        deltaVelocity.addY(overlapY);
    } else {
        onGround = false;
    }

    if (velocity.getY() > 0 && overlapY != 0) {
        velocity.subtractY(overlapY);
    } else if (velocity.getY() < 0 && overlapY != 0) {
        velocity.addY(overlapY);
    }*/