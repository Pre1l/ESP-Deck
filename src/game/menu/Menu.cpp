#include "game/menu/Menu.hpp"
#include "display/DisplayManager.hpp"
#include "bitmaps/GreenBrickBackgroundBitmap.hpp"
#include "game/snake/SnakeMenu.hpp"
#include "game/menu/GameMenu.hpp"
#include "game/menu/EspDeckMenu.hpp"

Menu::Menu() 
{
    DisplayManager::getDisplay().fillRect(0, 0, 80, 320, 0x18e3);
    DisplayManager::getDisplay().drawRect(0, 0, 80, 320, TFT_CYAN);

    focusOnSideMenu = true;
    menuIndex = 0;
    GameMenu::init();
    gameMenus.push_back(std::unique_ptr<GameMenu>(new EspDeckMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new SnakeMenu()));
    gameMenus[0]->renderMenu();
}

void Menu::update() 
{
    delay(10);
}

void Menu::onGameClosed() 
{
    
}

void Menu::keyPressed(int key) 
{
    if (key == 2 && focusOnSideMenu == false) {
        DisplayManager::getDisplay().drawRect(0, 0, 80, 320, TFT_CYAN);
        DisplayManager::getDisplay().drawRect(80, 0, 400, 320, 0x18e3);
        focusOnSideMenu = true;
    } else if (key == 0 && focusOnSideMenu == true) {
        DisplayManager::getDisplay().drawRect(0, 0, 80, 320, 0x18e3);
        DisplayManager::getDisplay().drawRect(80, 0, 400, 320, TFT_CYAN);
        focusOnSideMenu = false;
    } else if (!focusOnSideMenu) {
        if (key == 1) {
            gameMenus[menuIndex]->advanceSelectionUp();
        } else if (key == 3) {
            gameMenus[menuIndex]->advanceSelectionDown();
        } else if (key == 4) {
            gameMenus[menuIndex]->executeSelected();
        }
    } else if (focusOnSideMenu) {
        if (key == 1) {
            advanceSelectionUpAndExecute();
        } else if (key == 3) {
            advanceSelectionDownAndExecute();
        }
    }
}

void Menu::keyReleased(int key) 
{

}

void Menu::advanceSelectionDownAndExecute() 
{
    menuIndex--;
    if (menuIndex < 0) {
        menuIndex = gameMenus.size() -1;
    }
    gameMenus[menuIndex]->renderMenu();
}

void Menu::advanceSelectionUpAndExecute() 
{
    menuIndex++;
    if (menuIndex == gameMenus.size()) {
        menuIndex = 0;
    }
    gameMenus[menuIndex]->renderMenu();
}