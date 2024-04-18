#include "game/GameMenu.hpp"
#include "display/DisplayManager.hpp"

GameMenu::GameMenu() 
{
    DisplayManager::getDisplay().fillScreen(TFT_BLACK);
    DisplayManager::getImg().fillRect(0, 0, 200, 100, TFT_BLUE);
    DisplayManager::getImg().setTextColor(TFT_BLACK);
    DisplayManager::getImg().setTextSize(2);
    DisplayManager::getImg().drawCentreString("Snake", 100, 10, 4);
    DisplayManager::getImg().pushSprite(0, 0);
}

void GameMenu::update() 
{
    delay(1000);
}

void GameMenu::input(int key) 
{
    if (key == 1) {
        DisplayManager::getImg().scroll(0, 10);
        DisplayManager::getImg().pushSprite(0, 0);
    } else if (key == 2) {
        DisplayManager::getImg().scroll(0, -10);
        DisplayManager::getImg().pushSprite(0, 0);
    }
}