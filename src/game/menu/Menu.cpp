#include "game/menu/Menu.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/GreenBrickBackgroundBitmap.hpp"
#include "game/snake/SnakeMenu.hpp"
#include "game/menu/GameMenu.hpp"
#include "game/menu/EspDeckMenu.hpp"
#include "game/merge/MergeMenu.hpp"
#include "game/flappy-bird/FlappyBirdMenu.hpp"
#include "game/knight-game/KnightMenu.hpp"
#include "game/lights-out/LightsOutMenu.hpp"
#include <core/Core.hpp>

int Menu::menuReturnIndex = 0;

Menu::Menu() 
{
    gameType = GameType::MENU;
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.fillRect(0, 0, 60, 320, 0x18e3);
    drawMenuOutline(59, 0, 421, 320, false, false);
    drawMenuOutline(0, 0, 60, 320, true, true);

    focusOnSideMenu = true;
    menuIndex = menuReturnIndex;

    GameMenu::init();
    gameMenus.push_back(std::unique_ptr<GameMenu>(new EspDeckMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new SnakeMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new FlappyBirdMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new KnightMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new LightsOutMenu()));
    gameMenus.push_back(std::unique_ptr<GameMenu>(new MergeMenu()));
    menuButtonAmount = gameMenus.size();
    for (int i = 0; i < menuButtonAmount; i++) {
        display.pushImage(10, i*51 + 13, 40, 40, gameMenus[i]->getIconBitmap());
        for (int j = 4; j > 0; j--) {
            display.drawRoundRect(9, i*51 + 12, 42, 42, j, 0x18e3);
        }
    }
    highlightSelectedButton();

    gameMenus[menuIndex]->renderMenu();
}

void Menu::update(float deltaTime) 
{
    gameMenus[menuIndex]->update();
}

void Menu::keyPressed(Core::Key key) 
{
    if (key == Core::Key::LEFT && focusOnSideMenu == false) {
        drawMenuOutline(59, 0, 421, 320, false, false);
        drawMenuOutline(0, 0, 60, 320, true, true);
        focusOnSideMenu = true;
    } else if (key == Core::Key::RIGHT && focusOnSideMenu == true) {
        drawMenuOutline(0, 0, 60, 320, true, false);
        drawMenuOutline(59, 0, 421, 320, false, true);
        menuReturnIndex = menuIndex;
        focusOnSideMenu = false;
    } else if (!focusOnSideMenu) {
        if (key == Core::Key::UP) {
            gameMenus[menuIndex]->advanceSelectionUp();
        } else if (key == Core::Key::DOWN) {
            gameMenus[menuIndex]->advanceSelectionDown();
        } else if (key == Core::Key::ACTION) {
            if (menuIndex != 0) {
                drawMenuOutline(59, 0, 421, 320, false, false);
            }
            gameMenus[menuIndex]->executeSelected();
        }
    } else if (focusOnSideMenu) {
        if (key == Core::Key::UP) {
            advanceSelectionUpAndExecute();
        } else if (key == Core::Key::DOWN) {
            advanceSelectionDownAndExecute();
        }
    }
}

void Menu::keyReleased(Core::Key key) 
{

}

void Menu::drawMenuOutline(int x, int y, int width, int height, bool roundEdges, bool status) 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    uint16_t color;

    if (status) {
        color = 0xf820;
    } else {
        color = 0x18e3;
    }
    display.drawRect(x, y, width, height, color);
    if (roundEdges) {
        for (int i = 4; i > 0; i--) {
            display.drawRoundRect(x, y, width, height, i, color);
        }
    }
}

void Menu::advanceSelectionDownAndExecute() 
{
    unhighlightSelectedButton();
    upCountMenuIndex();
    highlightSelectedButton();
    gameMenus[menuIndex]->renderMenu();
}

void Menu::advanceSelectionUpAndExecute() 
{
    unhighlightSelectedButton();
    downCountMenuIndex();
    highlightSelectedButton();
    gameMenus[menuIndex]->renderMenu();
}

void Menu::downCountMenuIndex() 
{
    menuIndex--;
    if (menuIndex < 0) {
        menuIndex = menuButtonAmount - 1;
    }
}

void Menu::upCountMenuIndex() 
{
    menuIndex++;
    if (menuIndex == menuButtonAmount) {
        menuIndex = 0;
    }
}

void Menu::unhighlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(9, menuIndex*51 + 12, 42, 42, 4, 0x18e3);
    display.drawRoundRect(8, menuIndex*51 + 11, 44, 44, 6, 0x18e3);
}

void Menu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(9, menuIndex*51 + 12, 42, 42, 4, 0xf820);
    display.drawRoundRect(8, menuIndex*51 + 11, 44, 44, 6, 0xf820);
}