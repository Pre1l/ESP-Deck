#include "game/GameMenu.hpp"
#include "display/DisplayManager.hpp"

GameMenu::GameMenu() 
{
    
}

void GameMenu::update() 
{
    DisplayManager::getDisplay().fillScreen(TFT_BLACK);
    DisplayManager::getImg().fillRect(0, 0, 200, 100, TFT_BLUE);
    DisplayManager::getImg().setTextColor(TFT_BLACK);
    DisplayManager::getImg().setTextSize(2);
    DisplayManager::getImg().drawCentreString("Snake", 100, 10, 4);
    DisplayManager::getImg().pushSprite(0, 80);

    delay(1000);
    for (int i = 20; i <= 280; i += 20) {
        DisplayManager::getImg().pushSprite(i, 80);
        DisplayManager::getDisplay().fillRect(i - 20, 80, 20, 100, TFT_BLACK);
    }
    delay(1000);
}

void GameMenu::input(int key) 
{

}