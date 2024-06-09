#include "game/knight-game/entity/Entity.hpp"

#include <iostream>
#include <HardwareSerial.h>
#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>

Entity::Entity(std::shared_ptr<Vector2D> position, Hitbox hitbox) 
: position(position),
  hitbox(hitbox)
{
    
}

void Entity::update(float offsetX, float deltaTime) 
{
    clearAfterImageOffset(offsetX);
}

std::shared_ptr<Vector2D> Entity::getPosition() 
{
    return position;
}

Hitbox& Entity::getHitbox() 
{
    return hitbox;
}

void Entity::disableOffset() 
{
    offset = false;
}

void Entity::clearAfterImageOffset(float offsetX) 
{
    if (!offset)
        return;

    Vector2D position = *getPosition();
    TFT_eSPI& display = DisplayManager::getDisplay();

    float movementX = offsetX - lastOffsetX;
    int ceilMovementX = ceil(abs(movementX));
    int offsetPosX = round(position.getX() + lastOffsetX);
    int posY = position.getIntY();
    int width = getDrawWidth();
    int height = getDrawHeight();

    if (movementX != 0) {
        if (movementX > 0) {
            display.fillRect(offsetPosX, posY, ceilMovementX + 3, height + 1, TFT_BLACK);
        } else if (movementX < 0) {
            display.fillRect(offsetPosX + width - ceilMovementX, posY, ceilMovementX + 3, height + 1, TFT_BLACK);
        }
    }

    lastOffsetX = offsetX;
}

float Entity::getDrawWidth() 
{
    return getHitbox().getWidth() - 2;
}

float Entity::getDrawHeight() 
{
    return getHitbox().getHeight() - 2;
}

float Entity::getOffsetX() 
{
    return lastOffsetX;
}