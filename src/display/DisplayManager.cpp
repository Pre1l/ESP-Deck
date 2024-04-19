#include "display/DisplayManager.hpp"

TFT_eSPI DisplayManager::tft = TFT_eSPI();

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
}

TFT_eSPI& DisplayManager::getDisplay() 
{
    return tft;
}