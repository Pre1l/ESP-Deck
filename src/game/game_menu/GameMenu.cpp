#include "game/game_menu/GameMenu.hpp"
#include "display/DisplayManager.hpp"
#include "bitmaps/GreenBrickBackgroundBitmap.hpp"

TFT_eSprite gameMenuSprite = TFT_eSprite(&DisplayManager::tft);

GameMenu::GameMenu() 
{
    focusOnSideMenu = false;

    DisplayManager::getDisplay().fillRect(0, 0, 80, 320, 0x18e3);
    DisplayManager::getDisplay().pushImage(80, 0, 480, 320, greenBrickBackgroundBitmap);
}

void GameMenu::update() 
{
    delay(10);
}

void GameMenu::keyPressed(int key) 
{
    if (key == 2 && focusOnSideMenu == false) {
        DisplayManager::getDisplay().drawRect(0, 0, 80, 320, TFT_CYAN);
        DisplayManager::getDisplay().drawRect(80, 0, 400, 320, 0x18e3);
        focusOnSideMenu = true;
    } else if (key == 0 && focusOnSideMenu == true) {
        DisplayManager::getDisplay().drawRect(0, 0, 80, 320, 0x18e3);
        DisplayManager::getDisplay().drawRect(80, 0, 400, 320, TFT_CYAN);
        focusOnSideMenu = false;
    } else if (key == 1) {

    } else if (key == 3) {

    }
}

void GameMenu::keyReleased(int key) 
{

}