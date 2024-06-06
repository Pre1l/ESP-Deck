#include "game/knight-game/entity/CombatEntity.hpp"

#include <game/knight-game/KnightGame.hpp>

uint8_t CombatEntity::nextId = 0;

CombatEntity::CombatEntity(std::shared_ptr<Vector2D> position, int animationWidth, int animationHeight, int attackAnimationWidth, Vector2D velocity) 
: Entity(position, Hitbox(position, animationWidth + 2, animationHeight + 2)),
  attackAnimation({}, 0, attackAnimationWidth, animationHeight, 0, 0, 0, attackSprite, this),
  deathAnimation({}, 0, animationWidth, animationHeight, 0, 0, 0, deathSprite, this),
  movementAnimation({}, 0, animationWidth, animationHeight, 0, 0, movementSprite),
  velocity(velocity),
  attackHitboxRight(getPosition(), attackAnimationWidth - animationWidth, animationHeight + 2, animationWidth + 2),
  attackHitboxLeft(getPosition(), attackAnimationWidth - animationWidth, animationHeight + 2, -attackAnimationWidth + animationWidth - 2)
{
    this->animationWidth = animationWidth;
    this->animationHeight = animationHeight;
    this->attackAnimationWidth = attackAnimationWidth;
    this->id = nextId;
    nextId++;

    getMovementSprite().setSwapBytes(true);
    getMovementSprite().createSprite(animationWidth, animationHeight);
    getAttackSprite().setSwapBytes(true);
    getAttackSprite().createSprite(attackAnimationWidth, animationHeight);
    getDeathSprite().setSwapBytes(true);
}

void CombatEntity::update(float offsetX, float deltaTime)
{
    clearAfterImageOffset(offsetX);

    if (dead) {
        pushDeathSprite();
        deathAnimation.update(deltaTime);
        return;
    }

    if (attackRequest) {
        attackRequest = false;

        ProxyHitbox& attackHitbox = isFacingRight() ? attackHitboxRight : attackHitboxLeft;

        if (KnightGame::getInstance()->calculateTerrainCollision(attackHitbox, Rectangle::CollisionAxis::X, false) == 0) {
            setAttackAnimation();
            attackAnimation.update(deltaTime);
        }
    }

    handleVelocity(deltaTime);
    handleAnimation(deltaTime);

    if (attackAnimation.animationInProgress == true) {
        pushAttackSprite();
    } else {
        pushMovementSprite();
    }
}

CallbackAnimation& CombatEntity::getDeathAnimation() 
{
    return deathAnimation;
}

CallbackAnimation& CombatEntity::getAttackAnimation() 
{
    return attackAnimation;
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
        stopCallbackAnimation();
        facingDirection = Direction::RIGHT;
        running = true;
    } else if (runLeftRequest) {
        velocity.setX(-stats.speedX);
        stopCallbackAnimation();
        facingDirection = Direction::LEFT;
        running = true;
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
    if (attackAnimation.animationInProgress) {
        attackAnimation.stop();
        clearAfterImageAttackAnimation();
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
        display.fillRect(round(getPosition()->getX() + lastOffsetX) + 1, round(getPosition()->getY()), animationWidth, round(deltaVelocity.getY()) + 1, TFT_BLACK);
    } else if (deltaVelocity.getY() < 0) {
        display.fillRect(round(getPosition()->getX() + lastOffsetX) + 1, round(getPosition()->getY() + animationHeight + deltaVelocity.getY()), animationWidth, round(-deltaVelocity.getY()) + 1, TFT_BLACK);
    }

    if (deltaVelocity.getX() > 0) {
        display.fillRect(round(getPosition()->getX() + lastOffsetX) - 2, round(getPosition()->getY()), round(deltaVelocity.getX()) + 4, animationHeight + 1, TFT_BLACK);
    } else if (deltaVelocity.getX() < 0) {
        display.fillRect(round(getPosition()->getX() + lastOffsetX + animationWidth + deltaVelocity.getX()) - 2, round(getPosition()->getY()), round(-deltaVelocity.getX()) + 4, animationHeight + 1, TFT_BLACK);
    }
}

uint8_t CombatEntity::getId() 
{
    return id;
}

void CombatEntity::handleAnimation(float deltaTime) 
{
    if (attackAnimation.animationInProgress) {
        attackAnimation.update(deltaTime);
        return;
    }

    setAnimation();

    movementAnimation.update(deltaTime);
}

void CombatEntity::animationCallback()
{
    if (dead) {
        clearAfterImageDeath();
        std::shared_ptr<CombatEntity> selfPtr(this, [](CombatEntity*){});
        KnightGame::getInstance()->markCombatEntityForRemoval(selfPtr);
    }

    std::shared_ptr<KnightGame> knightGame = KnightGame::getInstance();
    ProxyHitbox& attackHitbox = isFacingRight() ? attackHitboxRight : attackHitboxLeft;

    std::vector<std::shared_ptr<CombatEntity>> collidingCombatEntities = knightGame->calculateCombatEntitiesCollision(attackHitbox);

    for (std::shared_ptr<CombatEntity> combatEntity : collidingCombatEntities) {
        combatEntity->takeDamage(stats.attackDamage);
    }
}

void CombatEntity::animationFinishedCallback() 
{
    clearAfterImageAttackAnimation();
}

void CombatEntity::clearAfterImageAttackAnimation() 
{
    if (isFacingRight()) {
        DisplayManager::getDisplay().fillRect(getPosition()->getIntX() + animationWidth, getPosition()->getIntY() + 1, attackAnimationWidth - animationWidth /*+ 1*/, animationHeight, TFT_BLACK);
        return;
    }

    DisplayManager::getDisplay().fillRect(getPosition()->getIntX() - attackAnimationWidth + animationWidth, getPosition()->getIntY() + 1, attackAnimationWidth - animationWidth /*+ 1*/, animationHeight, TFT_BLACK);
}

void CombatEntity::clearAfterImageDeath() 
{
    DisplayManager::getDisplay().fillRect(getPosition()->getIntX() + lastOffsetX + 1, getPosition()->getIntY() + 1, animationWidth, animationHeight, TFT_BLACK);
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
    dead = true;
    getMovementSprite().deleteSprite();
    getAttackSprite().deleteSprite();
    getDeathSprite().createSprite(getAnimationWidth(), getAnimationHeight());
    setDeathAnimation();
}

void CombatEntity::pushAttackSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();

    if (isFacingRight()) {
        attackSprite.pushSprite(position->getIntX() + lastOffsetX + 1, position->getIntY() + 1);
        return;
    }

    attackSprite.pushSprite(position->getIntX() + lastOffsetX + animationWidth + 1 - attackAnimationWidth, position->getIntY() + 1);
}

void CombatEntity::pushDeathSprite() 
{
    std::shared_ptr<Vector2D> position = getPosition();

    deathSprite.pushSprite(position->getIntX() + lastOffsetX + 1, position->getIntY() + 1);
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

TFT_eSprite& CombatEntity::getDeathSprite() 
{
    return deathSprite;
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