#include "game/knight-game/rectangle/Terrain.hpp"
#include <display/DisplayManager.hpp>

Terrain::Terrain(Vector2D* position, float width, float height, float offsetX, int16_t color) 
: Rectangle(position, width, height)
{
    this->color = color;
}

void Terrain::render(float offsetX) 
{
    float movementX = offsetX - lastOffsetX;

    int ceilMovementX = ceil(movementX);
    int floorMovementX = floor(movementX);

    Vector2D position = *getPosition();

    TFT_eSPI& display = DisplayManager::getDisplay();

    int offsetPosX = round(position.getX() + lastOffsetX);
    int posY = position.getIntY();
    int width = floor(getWidth());
    int height = floor(getHeight());

    if (movementX != 0) {
        if (movementX > 0) {
            display.fillRect(offsetPosX + ceilMovementX, posY, width, height, color);
            display.fillRect(offsetPosX - 1, posY, ceilMovementX + 2, height, TFT_BLACK);
        } else if (movementX < 0) {
            display.fillRect(offsetPosX + floorMovementX, posY, width, height, color);
            display.fillRect(offsetPosX + width + ceilMovementX - 1, posY, -floorMovementX + 2, height, TFT_BLACK);
        }
    }

    lastOffsetX = offsetX;
}