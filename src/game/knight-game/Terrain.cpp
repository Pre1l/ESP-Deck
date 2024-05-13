#include "game/knight-game/Terrain.hpp"

Terrain::Terrain(Vector2D& position, float width, float height, int16_t color) 
: Rectangle(position, width, height)
{
    this->color = color;
}