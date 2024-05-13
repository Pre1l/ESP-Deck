#include "game/knight-game/Rectangle.hpp"

uint8_t Rectangle::nextId = 0;

Rectangle::Rectangle(Vector2D& position, float width, float height) 
{
    this->position = &position;
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