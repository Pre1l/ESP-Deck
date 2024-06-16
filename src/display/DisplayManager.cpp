#include "display/DisplayManager.hpp"
#include "font/Fonts.hpp"
#include <vector>
#include <iostream>

TFT_eSPI DisplayManager::tft = TFT_eSPI();

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.setFreeFont(FF25);
    tft.setTextSize(2);
}

TFT_eSPI& DisplayManager::getDisplay() 
{
    return tft;
}

void DisplayManager::resetFont() 
{
    tft.setFreeFont(FF25);
    tft.setTextSize(2);
}

void DisplayManager::renderPartialBitmap(int xPartialBitmap, int yPartialBitmap, int xOnBitmap, int yOnBitmap, int widthPartialBitmap, int heightPartialBitmap, int widthBitmap, int heightBitmap, const unsigned short* bitmap) 
{
    if (xOnBitmap + widthPartialBitmap > widthBitmap || yOnBitmap + heightPartialBitmap > heightBitmap) {
        std::cerr << "Error: Partial bitmap exceeds bounds of the source bitmap." << std::endl;
        return;
    }

    std::vector<unsigned short> partialVectorBitmap;
    partialVectorBitmap.reserve(widthPartialBitmap * heightPartialBitmap);

    int index = yOnBitmap * widthBitmap + xOnBitmap;

    for (int row = 0; row < heightPartialBitmap; row++) {
        for (int col = 0; col < widthPartialBitmap; col++) {
            partialVectorBitmap.push_back(bitmap[index + col]);
        }
        index += widthBitmap;
    }

    tft.pushImage(xPartialBitmap, yPartialBitmap, widthPartialBitmap, heightPartialBitmap, partialVectorBitmap.data());
}