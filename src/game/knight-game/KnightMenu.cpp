#include "game/knight-game/KnightMenu.hpp"
#include "bitmap/knight-game/CastleBackgroundBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/snake/Snake.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/TrophyGoldenBitmap.hpp"
#include <game/menu/Menu.hpp>
#include "eeprom/EepromManager.hpp"
#include <game/knight-game/KnightGameController.hpp>

KnightMenu::KnightMenu() 
{

}

void KnightMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 1;

    backgroundSprite.pushImage(-60, -1, 480, 320, castleBackgroundBitmap);
    backgroundSprite.pushSprite(60, 1);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF30);
    display.setTextColor(0x4cb3);
    display.drawString("Knight Beta", 115, 40);
    DisplayManager::resetFont();
    display.fillRoundRect(160, 110, 180, 50, 10, 0x834c);
    display.drawString("Start", 210, 119);

    display.setTextColor(0xF440);
    display.setTextSize(1);
    display.setFreeFont(FF26);

    highlightSelectedButton();
    DisplayManager::resetFont();
}

void KnightMenu::update() 
{
    
}

void KnightMenu::advanceSelectionDown()
{
    unhighlightSelectedButton();
    upCountMenuIndex();
    highlightSelectedButton();
}

void KnightMenu::advanceSelectionUp()
{
    unhighlightSelectedButton();
    downCountMenuIndex();
    highlightSelectedButton();
}

void KnightMenu::unhighlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(160, menuIndex*60 + 110, 180, 50, 10, TFT_DARKGREY);
    display.drawRoundRect(161, menuIndex*60 + 111, 178, 48, 8, TFT_DARKGREY);
}

void KnightMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(160, menuIndex*60 + 110, 180, 50, 10, TFT_DARKGREY);
    display.drawRoundRect(161, menuIndex*60 + 111, 178, 48, 8, TFT_DARKGREY);
}

void KnightMenu::executeSelected()
{
    Core::setCurrentGame(std::unique_ptr<KnightGameController>(new KnightGameController()));
}