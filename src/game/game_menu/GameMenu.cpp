#include "game/game_menu/GameMenu.hpp"
#include "display/DisplayManager.hpp"
#include "bitmaps/SnakeBitmap.hpp"

GameMenu::GameMenu() 
{
    focusOnSideMenu = false;

    DisplayManager::getDisplay().fillScreen(TFT_BLACK);
    DisplayManager::getDisplay().fillRect(0, 0, 100, 320, TFT_DARKGREY);
    DisplayManager::getDisplay().fillRect(100, 0, 380, 320, TFT_RED);
    /*snakeSprite.createSprite(30, 30);
    snakeSprite.setSwapBytes(true);
    snakeSprite.pushImage(0, 0, 150, 120, snakeBitmap);
    snakeSprite.pushSprite(0, 0);*/
}

void GameMenu::update() 
{
    delay(1);
}

void GameMenu::input(int key) 
{
    if (key == 2 && focusOnSideMenu == false) {
        DisplayManager::getDisplay().fillRect(0, 0, 200, 320, TFT_DARKGREY);
        DisplayManager::getDisplay().drawRect(0, 0, 200, 320, TFT_BLUE);
        DisplayManager::getDisplay().drawRect(200, 0, 280, 320, TFT_RED);
        focusOnSideMenu = true;
    } else if (key == 0 && focusOnSideMenu == true) {
        DisplayManager::getDisplay().fillRect(100, 0, 380, 320, TFT_RED);
        DisplayManager::getDisplay().drawRect(100, 0, 380, 320, TFT_BLUE);
        DisplayManager::getDisplay().drawRect(0, 0, 100, 320, TFT_DARKGREY);
        focusOnSideMenu = false;
    }
}