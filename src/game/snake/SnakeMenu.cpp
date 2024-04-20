#include "game/snake/SnakeMenu.hpp"
#include "bitmaps/GreenBrickBackgroundBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/snake/Snake.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include "bitmaps/TrophyGoldenBitmap.hpp"
#include <EEPROM.h>
#include "config/eepromConfig.hpp"

SnakeMenu::SnakeMenu() 
{

}

void SnakeMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-80, 0, 480, 320, greenBrickBackgroundBitmap);
    backgroundSprite.pushSprite(80, 0);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF32);
    display.setTextColor(0x576a);
    display.drawString("Snake", 135, 40);
    DisplayManager::resetFont();
    display.fillRoundRect(320, 135, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(160, 130, 180, 50, 10, 0x3366);
    display.pushImage(340, 138, 35, 35, trophyGoldenBitmap);
    display.drawString("Classic", 188, 139);

    display.fillRoundRect(320, 195, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(160, 190, 180, 50, 10, 0x3366);
    display.pushImage(340, 198, 35, 35, trophyGoldenBitmap);
    display.drawString("Speed", 192, 199);

    display.fillRoundRect(320, 255, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(160, 250, 180, 50, 10, 0x3366);
    display.pushImage(340, 258, 35, 35, trophyGoldenBitmap);
    display.drawString("Rising", 195, 259);

    int highscores[] = {
        EEPROM.read(EEPROM_SNAKE_CLASSIC_HIGHSCORE_ADDR),
        EEPROM.read(EEPROM_SNAKE_SPEED_HIGHSCORE_ADDR),
        EEPROM.read(EEPROM_SNAKE_RISING_HIGHSCORE_ADDR)
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
    display.drawString(highscoreStrings[0], 374, 146);
    display.drawString(highscoreStrings[1], 374, 206);
    display.drawString(highscoreStrings[2], 374, 266);

    highlightSelectedButton();
    DisplayManager::resetFont();
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
    display.drawRoundRect(160, menuIndex*60 + 130, 180, 50, 10, 0x3366);
    display.drawRoundRect(161, menuIndex*60 + 131, 178, 48, 8, 0x3366);
}

void SnakeMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(160, menuIndex*60 + 130, 180, 50, 10, 0x576a);
    display.drawRoundRect(161, menuIndex*60 + 131, 178, 48, 8, 0x576a);
}

void SnakeMenu::executeSelected()
{
    DisplayManager::getDisplay().drawRect(80, 0, 400, 320, 0x18e3);
    std::unique_ptr<Game> newGame(new Snake(menuIndex));
    setCurrentGame(std::move(newGame));
}