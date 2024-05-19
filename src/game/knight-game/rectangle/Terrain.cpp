#include "game/knight-game/rectangle/Terrain.hpp"
#include <display/DisplayManager.hpp>

Terrain::Terrain(Vector2D* position, float width, float height, float offsetX, int16_t color) 
: Rectangle(position, width, height)
{
    this->color = color;

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.fillRect(getPosition()->getIntX(), getPosition()->getIntY(), getWidth(), getHeight(), color);
}

void Terrain::render(float offsetX) 
{
    Vector2D position = *getPosition();
    TFT_eSPI& display = DisplayManager::getDisplay();

    float movementX = offsetX - lastOffsetX;
    int ceilMovementX = ceil(abs(movementX));;
    int offsetPosX = ceil(position.getX() + lastOffsetX);
    int posY = position.getIntY();
    int width = ceil(getWidth());
    int height = ceil(getHeight());

    if (movementX != 0) {
        if (movementX > 0) {
            display.fillRect(offsetPosX - 1, posY, ceilMovementX + 2, height, TFT_BLACK);
            display.fillRect(offsetPosX + width - ceilMovementX - 3, posY, ceilMovementX + 3, height, color); 
        } else if (movementX < 0) {
            display.fillRect(offsetPosX + width - ceilMovementX - 1, posY, ceilMovementX + 2, height, TFT_BLACK);
            display.fillRect(offsetPosX, posY, ceilMovementX + 3, height, color);
        }
    }

    lastOffsetX = offsetX;
}