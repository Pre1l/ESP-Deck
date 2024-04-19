#include "display/DisplayManager.hpp"
#include "fonts/Fonts.hpp";

TFT_eSPI DisplayManager::tft = TFT_eSPI();

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setSwapBytes(true);
    tft.setFreeFont(FF25);
}

TFT_eSPI& DisplayManager::getDisplay() 
{
    return tft;
}

int DisplayManager::rgb(int r, int g, int b) 
{
    return (r << (5 + 6)) | (g << 5) | b;
}