#include "game/Game.hpp"
#include "display/DisplayManager.hpp"
#include <vector>

void Game::renderPartialBitmap(int x, int y, int bitmapX, int bitmapY, int width, int height, int bitmapWidth, int bitmapHeight, const unsigned short* bitmap) 
{
    std::vector<unsigned short> paritalVectorBitmap;
    int index = bitmapY * bitmapWidth + bitmapX;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            paritalVectorBitmap.push_back(bitmap[index]);
            index++;
        }
        index += bitmapWidth - width;
    }

    unsigned short paritalBitmap[width * height];

    for (int i = 0; i < paritalVectorBitmap.size(); i++) {
        paritalBitmap[i] = paritalVectorBitmap[i];
    }

    DisplayManager::getDisplay().pushImage(x, y, width, height, paritalBitmap);
}