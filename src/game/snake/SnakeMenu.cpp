#include "game/snake/SnakeMenu.hpp"
#include "bitmap/GreenBrickBackgroundBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/snake/Snake.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/TrophyGoldenBitmap.hpp"
#include <game/menu/Menu.hpp>
#include "eeprom/EepromManager.hpp"

SnakeMenu::SnakeMenu() 
{

}

void SnakeMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-60, -1, 480, 320, greenBrickBackgroundBitmap);
    backgroundSprite.pushSprite(60, 1);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF32);
    display.setTextColor(0x576a);
    display.drawString("Snake", 125, 40);
    DisplayManager::resetFont();
    display.fillRoundRect(310, 135, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 130, 180, 50, 10, 0x3366);
    display.pushImage(330, 138, 35, 35, trophyGoldenBitmap);
    display.drawString("Classic", 178, 139);

    display.fillRoundRect(310, 195, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 190, 180, 50, 10, 0x3366);
    display.pushImage(330, 198, 35, 35, trophyGoldenBitmap);
    display.drawString("Speed", 182, 199);

    display.fillRoundRect(310, 255, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(150, 250, 180, 50, 10, 0x3366);
    display.pushImage(330, 258, 35, 35, trophyGoldenBitmap);
    display.drawString("Rising", 185, 259);

    int highscores[] = {
        EepromManager::readInt8(EepromManager::EEPROM_SNAKE_CLASSIC_HIGHSCORE_ADDR_INT8),
        EepromManager::readInt8(EepromManager::EEPROM_SNAKE_SPEED_HIGHSCORE_ADDR_INT8),
        EepromManager::readInt8(EepromManager::EEPROM_SNAKE_RISING_HIGHSCORE_ADDR_INT8)
    };

    String highscoreStrings[] = {
        String(highscores[0]),
        String(highscores[1]),
        String(highscores[2])
    };

    for (int i = 0; i < 3; i++) {
        if (highscores[i] < 10) {
            highscoreStrings[i] = "00" + highscoreStrings[i];
        } else if (highscores[i] < 100) {
            highscoreStrings[i] = "0" + highscoreStrings[i];
        }
    }

    display.setTextColor(0xF440);
    display.setTextSize(1);
    display.setFreeFont(FF26);
    display.drawString(highscoreStrings[0], 364, 146);
    display.drawString(highscoreStrings[1], 364, 206);
    display.drawString(highscoreStrings[2], 364, 266);

    highlightSelectedButton();
    DisplayManager::resetFont();
}

void SnakeMenu::update() 
{
    
}

void SnakeMenu::advanceSelectionDown()
{
    unhighlightSelectedButton();
    upCountMenuIndex();
    highlightSelectedButton();
}

void SnakeMenu::advanceSelectionUp()
{
    unhighlightSelectedButton();
    downCountMenuIndex();
    highlightSelectedButton();
}

void SnakeMenu::unhighlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(150, menuIndex*60 + 130, 180, 50, 10, 0x3366);
    display.drawRoundRect(151, menuIndex*60 + 131, 178, 48, 8, 0x3366);
}

void SnakeMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(150, menuIndex*60 + 130, 180, 50, 10, 0x576a);
    display.drawRoundRect(151, menuIndex*60 + 131, 178, 48, 8, 0x576a);
}

void SnakeMenu::executeSelected()
{
    std::unique_ptr<Game> newGame(new Snake(menuIndex));
    Core::setCurrentGame(std::move(newGame));
}