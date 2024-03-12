#include "game/GameMenu.hpp"
#include "display/DisplayManager.hpp"

GameMenu::GameMenu() 
{
    DisplayManager::getDisplay().fillScreen(TFT_RED);
}

void GameMenu::update() 
{
    delay(1000);
    DisplayManager::getDisplay().fillScreen(TFT_BLACK);
    delay(1000);
    DisplayManager::getDisplay().fillScreen(TFT_RED);
}

void GameMenu::input(int key) 
{

}