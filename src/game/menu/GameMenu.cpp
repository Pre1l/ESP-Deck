#include "game/menu/GameMenu.hpp"

TFT_eSprite GameMenu::backgroundSprite(&DisplayManager::tft);

void GameMenu::init() {
    backgroundSprite.createSprite(420, 320);
    backgroundSprite.setSwapBytes(true);
}

void GameMenu::downCountMenuIndex() 
{
    menuIndex--;
    if (menuIndex < 0) {
        menuIndex = menuButtonAmount - 1;
    }
}

void GameMenu::upCountMenuIndex() 
{
    menuIndex++;
    if (menuIndex == menuButtonAmount) {
        menuIndex = 0;
    }
}