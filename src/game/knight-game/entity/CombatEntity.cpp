#include "game/knight-game/entity/CombatEntity.hpp"
#include <game/knight-game/KnightGame.hpp>

CombatEntity::CombatEntity(std::shared_ptr<Vector2D> position, int animationWidth, int animationHeight, int attackAnimationWidth, Vector2D velocity) 
: Entity(position, Hitbox(position, animationWidth + 2, animationHeight + 2)),
  AnimationObserver(CallbackAnimation({}, 0, attackAnimationWidth, animationHeight, 0, 0, 0, attackSprite, this)),
  movementAnimation({}, 0, animationWidth, animationHeight, 0, 0, movementSprite),
  velocity(velocity)
{
    this->animationWidth = animationWidth;
    this->animationHeight = animationHeight;
    this->attackAnimationWidth = attackAnimationWidth;
    getMovementSprite().setSwapBytes(true);
    getMovementSprite().createSprite(animationWidth, animationHeight);
    getAttackSprite().setSwapBytes(true);
    getAttackSprite().createSprite(attackAnimationWidth, animationHeight);
}

void CombatEntity::update(float deltaTime)
{
    if (attackRequest) {
        attackRequest = false;

        Hitbox attackHitbox(std::make_shared<Vector2D>(getPosition()->getX() + animationWidth + 2, getPosition()->getY()), attackAnimationWidth - animationWidth, animationHeight + 2);
        if (KnightGame::getInstance()->calculateTerrainCollision(attackHitbox, Rectangle::COLLISION_X, false) == 0) {
            callbackAnimation.update(deltaTime);
        }
    }

    handleVelocity(deltaTime);
    handleAnimation(deltaTime);

    if (callbackAnimation.animationInProgress) {
        pushAttackSprite();
    } else {
        pushMovementSprite();
    }
}

void CombatEntity::handleVelocity(float deltaTime) 
{
    Hitbox& hitbox = getHitbox();
     std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
    Vector2D& velocity = getVelocity();

    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(0.7);
        jumpRequest = false;
        stopCallbackAnimation();
    }

    if (runRightRequest && runLeftRequest) {
        velocity.setX(0);
        running = false;
    } else if (runRightRequest) {
        velocity.setX(0.2);
        facingDirection = RIGHT;
        running = true;
        stopCallbackAnimation();
    } else if (runLeftRequest) {
        velocity.setX(-0.2);
        facingDirection = LEFT;
        running = true;
        stopCallbackAnimation();
    } else {
        velocity.setX(0);
        running = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);
    clearAfterImage(deltaVelocity);

    getPosition()->addX(deltaVelocity.getX());
    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_X, true);

    if (deltaVelocity.getX() > 0 && overlapX != 0) {
        getPosition()->subtractX(overlapX);
        velocity.setX(0);
        running = false;
    } else if (deltaVelocity.getX() < 0 && overlapX != 0) {
        getPosition()->addX(overlapX);
        velocity.setX(0);
        running = false;
    }

    getPosition()->addY(deltaVelocity.getY());
    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::COLLISION_Y, true);

    if (deltaVelocity.getY() > 0 && overlapY != 0) {
        getPosition()->subtractY(overlapY);
        velocity.setY(0);
        onGround = true;
    } else if (deltaVelocity.getY() < 0 && overlapY != 0) {
        getPosition()->addY(overlapY);
        velocity.setY(0);
    } else {
        onGround = false;
    }
}

void CombatEntity::stopCallbackAnimation() 
{
    if (callbackAnimation.animationInProgress) {
        callbackAnimation.stop();
        clearCallbackAnimationAfterImage();
    }
}

void CombatEntity::clearAfterImage(Vector2D& deltaVelocity) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    if (deltaVelocity.getY() > 0) {
        display.fillRect(getPosition()->getIntX(), ceil(getPosition()->getY()), animationWidth, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(getPosition()->getIntX(), ceil(getPosition()->getY() + animationHeight + deltaVelocity.getIntY()), animationWidth, ceil(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }

    if (deltaVelocity.getX() > 0) {
        display.fillRect(getPosition()->getIntX() - 1, ceil(getPosition()->getIntY()), ceil(deltaVelocity.getX()) + 1, animationHeight + 1, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(getPosition()->getIntX() + animationWidth + ceil(deltaVelocity.getX()) - 1, ceil(getPosition()->getIntY()), ceil(-deltaVelocity.getX()) + 1, animationHeight + 1, TFT_BLACK);
    }
}

void CombatEntity::handleAnimation(float deltaTime) 
{
    if (callbackAnimation.animationInProgress) {
        callbackAnimation.update(deltaTime);
        return;
    }

    setAnimation();

    movementAnimation.update(deltaTime);
}

void CombatEntity::animationCallback()
{
    // Do damage to Entities in attackhitbox
}

void CombatEntity::animationFinishedCallback() 
{
    clearCallbackAnimationAfterImage();
}

void CombatEntity::clearCallbackAnimationAfterImage() 
{
    DisplayManager::getDisplay().fillRect(getPosition()->getIntX() + animationWidth, getPosition()->getIntY() + 1, attackAnimationWidth - animationWidth /*+ 1*/, animationHeight, TFT_BLACK);
}

void CombatEntity::pushMovementSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();
    movementSprite.pushSprite(position->getIntX() + 1, position->getIntY() + 1);
}

void CombatEntity::pushAttackSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();
    attackSprite.pushSprite(position->getIntX() + 1, position->getIntY() + 1);
}

void CombatEntity::attack()
{
    if (onGround) {
        attackRequest = true;
        stopRunning(LEFT);
        stopRunning(RIGHT);
    }
}

void CombatEntity::jump() 
{
    if (onGround) {
        jumpRequest = true;
    }
}

void CombatEntity::startRunning(int direction) 
{
    direction == RIGHT ? runRightRequest = true : runLeftRequest = true;
}

void CombatEntity::stopRunning(int direction) 
{
    direction == RIGHT ? runRightRequest = false : runLeftRequest = false;
}

Animation& CombatEntity::getMovementAnimation() 
{
    return movementAnimation;
}

int CombatEntity::getAttackAnimationWidth() 
{
    return attackAnimationWidth;
}

int CombatEntity::getAnimationWidth() 
{
    return animationWidth;
}

int CombatEntity::getAnimationHeight() 
{
    return animationHeight;
}

Vector2D& CombatEntity::getVelocity() 
{
    return velocity;
}

TFT_eSprite& CombatEntity::getAttackSprite() 
{
    return attackSprite;
}

TFT_eSprite& CombatEntity::getMovementSprite() 
{
    return movementSprite;
}