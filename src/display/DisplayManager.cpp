#include "display/DisplayManager.hpp"
#include "font/Fonts.hpp"
#include <vector>

TFT_eSPI DisplayManager::tft = TFT_eSPI();

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(1);
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

void DisplayManager::renderPartialBitmap(int xPartialBitmap, int yPartialBitmap, int xOnBitmap, int yOnBitmap, int widthPartialBitmap, int heightPartialBitmap, int widthBitmap, const unsigned short* bitmap) 
{
    std::vector<unsigned short> paritalVectorBitmap;
    int index = yOnBitmap * widthBitmap + xOnBitmap;

    for (int row = 0; row < heightPartialBitmap; row++) {
        for (int col = 0; col < widthPartialBitmap; col++) {
            paritalVectorBitmap.push_back(bitmap[index]);
            index++;
        }
        index += widthBitmap - widthPartialBitmap;
    }

    unsigned short paritalBitmap[widthPartialBitmap * heightPartialBitmap];

    for (int i = 0; i < paritalVectorBitmap.size(); i++) {
        paritalBitmap[i] = paritalVectorBitmap[i];
    }

    tft.pushImage(xPartialBitmap, yPartialBitmap, widthPartialBitmap, heightPartialBitmap, paritalBitmap);
}