#include "display/DisplayManager.hpp"

TFT_eSPI DisplayManager::tft = TFT_eSPI();
TFT_eSprite DisplayManager::img = TFT_eSprite(&tft);

void DisplayManager::initialize() 
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    img.createSprite(200, 320);
    img.setColorDepth(16);
    img.setScrollRect(0, 0, 200, 320, TFT_GREEN);
}

TFT_eSPI& DisplayManager::getDisplay() 
{
    return tft;
}

TFT_eSprite& DisplayManager::getImg() 
{
    return img;
}