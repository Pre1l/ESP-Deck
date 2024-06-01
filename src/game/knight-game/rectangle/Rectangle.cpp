#include "game/knight-game/rectangle/Rectangle.hpp"
#include <HardwareSerial.h>
#include <memory>

uint8_t Rectangle::nextId = 0;

Rectangle::Rectangle(std::shared_ptr<Vector2D> position, float width, float height) 
: position(position)
{
    this->width = width;
    this->height = height;
    this->id = nextId;
    nextId++;
}

std::shared_ptr<Vector2D> Rectangle::getPosition() 
{
    return position;
}

float Rectangle::getWidth() 
{
    return width;
}

float Rectangle::getHeight() 
{
    return height;
}

uint8_t Rectangle::getId() 
{
    return id;
}

float Rectangle::calculateCollision(Rectangle& other, CollisionAxis axis, bool returnOverlap) 
{
    Vector2D pos = *getPosition();
    float x = pos.getX();
    float y = pos.getY();
    float width = getWidth();
    float height = getHeight();

    Vector2D oPos = *other.getPosition();
    float oX = oPos.getX();
    float oY = oPos.getY();
    float oWidth  = other.getWidth();
    float oHeight = other.getHeight();

    bool collideX = (x < oX + oWidth) && (x + width > oX);
    bool collideY = (y < oY + oHeight) && (y + height > oY);

    if (!collideX || !collideY) {
        return 0;
    }

    if (axis == CollisionAxis::X && collideX) {
        float overlapLeft = oX + oWidth - x;
        float overlapRight = x + width - oX;
        float overlapX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;

        if (!returnOverlap) {
            if (overlapX != 0)
                return 1;

            return 0;
        }

        if (overlapX == width || overlapX == oWidth) {
            return 0;
        }

        if (overlapX < 0) {
            return overlapX - 0.0001;
        } else if (overlapX > 0) {
            return overlapX + 0.0001;
        }

        return overlapX;
    } else if (axis == CollisionAxis::Y && collideY) {
        float overlapTop = oY + oHeight - y;
        float overlapBottom = y + height - oY;
        float overlapY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

        if (!returnOverlap) {
            if (overlapY != 0)
                return 1;

            return 0;
        }

        if (overlapY == height || overlapY == oHeight) {
            return 0;
        }

        if (overlapY < 0) {
            return overlapY - 0.0001;
        } else if (overlapY > 0) {
            return overlapY + 0.0001;
        }

        return overlapY;
    }

    return 0;
}