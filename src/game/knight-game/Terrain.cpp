#include "game/knight-game/Terrain.hpp"
#include <display/DisplayManager.hpp>

Terrain::Terrain(Vector2D* position, float width, float height, int16_t color) 
: Rectangle(position, width, height)
{
    this->color = color;
    render();
}

void Terrain::render() 
{
    Vector2D position = *getPosition();
    DisplayManager::getDisplay().fillRect(position.getIntX(), position.getIntY(), getWidth(), getHeight(), color);
}