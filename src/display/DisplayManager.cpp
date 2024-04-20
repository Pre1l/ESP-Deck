#include "display/DisplayManager.hpp"
#include "font/Fonts.hpp"

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