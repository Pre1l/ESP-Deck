#include "display/DisplayManager.hpp"

TFT_eSPI DisplayManager::tft = TFT_eSPI();
TFT_eSprite DisplayManager::img = TFT_eSprite(&tft);

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    img.createSprite(200, 100);
    img.setColorDepth(8);
}

TFT_eSPI& DisplayManager::getDisplay() 
{
    return tft;
}

TFT_eSprite& DisplayManager::getImg() 
{
    return img;
}