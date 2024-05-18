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
    lastOffsetX = offsetX;

    Vector2D position = *getPosition();

    TFT_eSPI& display = DisplayManager::getDisplay();

    int offsetPosX = round(position.getX() + lastOffsetX);
    int posY = position.getIntY();
    int width = getWidth();
    int height = getHeight();

    if (movementX != 0) {
        if (movementX > 0) {
            display.fillRect(offsetPosX - 10, posY, movementX + 12, height, TFT_BLACK);
        } else if (movementX < 0) {
            display.fillRect(offsetPosX + width + movementX - 2, posY, -movementX + 10, height, TFT_BLACK);
        }

        display.fillRect(offsetPosX + movementX + 2, posY + 2, width - 4, height - 4, color);
    }
}