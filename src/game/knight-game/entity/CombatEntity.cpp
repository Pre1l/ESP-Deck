#include "game/knight-game/entity/CombatEntity.hpp"
#include <game/knight-game/KnightGame.hpp>

CombatEntity::CombatEntity(std::shared_ptr<Vector2D> position, int animationWidth, int animationHeight, int attackAnimationWidth, Vector2D velocity) 
: Entity(position, Hitbox(position, animationWidth + 2, animationHeight + 2)),
  AnimationObserver(CallbackAnimation({}, 0, attackAnimationWidth, animationHeight, 0, 0, 0, attackSprite, this)),
  movementAnimation({}, 0, animationWidth, animationHeight, 0, 0, movementSprite),
  velocity(velocity),
  attackHitboxRight(getPosition(), attackAnimationWidth - animationWidth, animationHeight + 2, animationWidth + 2),
  attackHitboxLeft(getPosition(), attackAnimationWidth - animationWidth, animationHeight + 2, -attackAnimationWidth + animationWidth - 2)
{
    this->animationWidth = animationWidth;
    this->animationHeight = animationHeight;
    this->attackAnimationWidth = attackAnimationWidth;
    getMovementSprite().setSwapBytes(true);
    getMovementSprite().createSprite(animationWidth, animationHeight);
    getAttackSprite().setSwapBytes(true);
    getAttackSprite().createSprite(attackAnimationWidth, animationHeight);
}

void CombatEntity::update(float offsetX, float deltaTime)
{
    if (attackRequest) {
        attackRequest = false;

        ProxyHitbox& attackHitbox = isFacingRight() ? attackHitboxRight : attackHitboxLeft;

        if (KnightGame::getInstance()->calculateTerrainCollision(attackHitbox, Rectangle::CollisionAxis::X, false) == 0) {
            callbackAnimation.update(deltaTime);
        }
    }

    handleVelocity(deltaTime);
    handleAnimation(deltaTime);
    clearAfterImageOffset(offsetX);

    if (callbackAnimation.animationInProgress) {
        pushAttackSprite();
    } else {
        pushMovementSprite();
    }
}

void CombatEntity::handleVelocity(float deltaTime) 
{
    std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
    Hitbox& hitbox = getHitbox();
    Vector2D& velocity = getVelocity();

    velocity.addY(0.05);
    if (jumpRequest == true) {
        velocity.subtractY(stats.jumpSpeed);
        jumpRequest = false;
        stopCallbackAnimation();
    }

    if (runRightRequest && runLeftRequest) {
        velocity.setX(0);
        running = false;
    } else if (runRightRequest) {
        velocity.setX(stats.speedX);
        facingDirection = Direction::RIGHT;
        running = true;
        stopCallbackAnimation();
    } else if (runLeftRequest) {
        velocity.setX(-stats.speedX);
        facingDirection = Direction::LEFT;
        running = true;
        stopCallbackAnimation();
    } else {
        velocity.setX(0);
        running = false;
    }

    Vector2D deltaVelocity = velocity.copy().multiply(deltaTime);
    clearAfterImageVelocity(deltaVelocity);

    getPosition()->addX(deltaVelocity.getX());
    float overlapX = knightGame->calculateCollision(hitbox, Rectangle::CollisionAxis::X, true);

    if (deltaVelocity.getX() != 0 && overlapX != 0) {
        std::shared_ptr<CombatEntity> collisionCombatEntity = knightGame->calculateCombatEntityCollision(hitbox, Rectangle::CollisionAxis::X);
        if (collisionCombatEntity != nullptr)
            collisionWithCombatEntity(collisionCombatEntity, Rectangle::CollisionAxis::X);

        deltaVelocity.getX() > 0 ? getPosition()->subtractX(overlapX) : getPosition()->addX(overlapX);
        velocity.setX(0);
        running = false;
    }

    getPosition()->addY(deltaVelocity.getY());
    float overlapY = knightGame->calculateCollision(hitbox, Rectangle::CollisionAxis::Y, true);

    if (deltaVelocity.getY() != 0 && overlapY != 0) {
        std::shared_ptr<CombatEntity> collisionCombatEntity = knightGame->calculateCombatEntityCollision(hitbox, Rectangle::CollisionAxis::Y);
        if (collisionCombatEntity != nullptr)
            collisionWithCombatEntity(collisionCombatEntity, Rectangle::CollisionAxis::Y);

        deltaVelocity.getY() > 0 ? getPosition()->subtractY(overlapY) : getPosition()->addY(overlapY);
        velocity.setY(0);
        if (deltaVelocity.getY() > 0)
            onGround = true;
    } else {
        onGround = false;
    }
}

void CombatEntity::stopCallbackAnimation() 
{
    if (callbackAnimation.animationInProgress) {
        callbackAnimation.stop();
        clearAfterImageCallbackAnimation();
    }
}

void CombatEntity::disableOffset() 
{
    offset = false;
}

void CombatEntity::clearAfterImageOffset(float offsetX) 
{
    if (!offset)
        return;

    Vector2D position = *getPosition();
    TFT_eSPI& display = DisplayManager::getDisplay();

    float movementX = offsetX - lastOffsetX;
    int ceilMovementX = ceil(abs(movementX));;
    int offsetPosX = ceil(position.getX() + lastOffsetX);
    int posY = position.getIntY();
    int width = getAnimationWidth();
    int height = getAnimationHeight();

    if (movementX != 0) {
        if (movementX > 0) {
            display.fillRect(offsetPosX - 2, posY, ceilMovementX + 3, height + 1, TFT_BLACK);
        } else if (movementX < 0) {
            display.fillRect(offsetPosX + width - ceilMovementX - 2, posY, ceilMovementX + 3, height + 1, TFT_BLACK);
        }
    }

    lastOffsetX = offsetX;
}

void CombatEntity::clearAfterImageVelocity(Vector2D& deltaVelocity) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    if (deltaVelocity.getY() > 0) {
        display.fillRect(getPosition()->getIntX() + lastOffsetX + 1, ceil(getPosition()->getY()), animationWidth, ceil(deltaVelocity.getIntY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(getPosition()->getIntX() + lastOffsetX + 1, ceil(getPosition()->getY() + animationHeight + deltaVelocity.getIntY()), animationWidth, ceil(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }

    if (deltaVelocity.getX() > 0) {
        display.fillRect(getPosition()->getIntX() + lastOffsetX - 1, ceil(getPosition()->getIntY()), ceil(deltaVelocity.getX()) + 1, animationHeight + 1, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(getPosition()->getIntX() + lastOffsetX + animationWidth + ceil(deltaVelocity.getX()) - 1, ceil(getPosition()->getIntY()), ceil(-deltaVelocity.getX()) + 1, animationHeight + 1, TFT_BLACK);
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
    std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
    ProxyHitbox& attackHitbox = isFacingRight() ? attackHitboxRight : attackHitboxLeft;

    std::vector<std::shared_ptr<CombatEntity>> collidingCombatEntities = knightGame->calculateCombatEntitiesCollision(attackHitbox);

    for (std::shared_ptr<CombatEntity> combatEntity : collidingCombatEntities) {
        combatEntity->takeDamage(stats.attackDamage);
    }
}

void CombatEntity::animationFinishedCallback() 
{
    clearAfterImageCallbackAnimation();
}

void CombatEntity::clearAfterImageCallbackAnimation() 
{
    DisplayManager::getDisplay().fillRect(getPosition()->getIntX() + animationWidth, getPosition()->getIntY() + 1, attackAnimationWidth - animationWidth /*+ 1*/, animationHeight, TFT_BLACK);
}

void CombatEntity::pushMovementSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();

    movementSprite.pushSprite(position->getIntX() + lastOffsetX + 1, position->getIntY() + 1);
}

void CombatEntity::takeDamage(float amount) 
{
    stats.health -= amount - amount*stats.armor/100;
    if (stats.health <= 0) {
        die();
    }
}

void CombatEntity::die() 
{
    startRunning(Direction::LEFT);
}

void CombatEntity::pushAttackSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();

    if (!offset) {
        attackSprite.pushSprite(position->getIntX() + 1, position->getIntY() + 1);
        return;
    }

    attackSprite.pushSprite(position->getIntX() + lastOffsetX + 1, position->getIntY() + 1);
}

void CombatEntity::attack()
{
    if (isOnGround()) {
        attackRequest = true;
        stopRunning(Direction::RIGHT);
        stopRunning(Direction::LEFT);
    }
}

void CombatEntity::jump() 
{
    if (isOnGround()) {
        jumpRequest = true;
    }
}

void CombatEntity::startRunning(Direction direction) 
{
    direction == Direction::RIGHT ? runRightRequest = true : runLeftRequest = true;
}

void CombatEntity::stopRunning(Direction direction) 
{
    direction == Direction::RIGHT ? runRightRequest = false : runLeftRequest = false;
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

bool CombatEntity::isRunning() 
{
    return running;
}

bool CombatEntity::isOnGround() 
{
    return onGround;
}

bool CombatEntity::isFacingRight()
{
    return facingDirection == Direction::RIGHT;
}

bool CombatEntity::isFacingLeft()
{
    return facingDirection == Direction::LEFT;
}

CombatEntity::Type CombatEntity::getType() 
{
    return type;
}