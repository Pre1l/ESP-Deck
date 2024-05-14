#include "game/knight-game/Rectangle.hpp"

uint8_t Rectangle::nextId = 0;

Rectangle::Rectangle(Vector2D* position, float width, float height) 
: position(position)
{
    this->width = width;
    this->height = height;
    this->id = nextId;
    nextId++;
}

Vector2D* Rectangle::getPosition() 
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

bool Rectangle::intersects(Rectangle& other) 
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

    bool intersectX = (x < oX + oWidth) && (x + width > oX);
    bool intersectY = (y < oY + oHeight) && (y + height > oY);

    return intersectX && intersectY;
}