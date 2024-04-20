#include "game/menu/GameMenu.hpp"

TFT_eSprite GameMenu::backgroundSprite(&DisplayManager::tft);

void GameMenu::init() {
    backgroundSprite.createSprite(400, 320);
    backgroundSprite.setSwapBytes(true);
}