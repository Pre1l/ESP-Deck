#include "game/flappyBird/FlappyBirdMenu.hpp"
#include "bitmap/flappyBird/SkyBackgroundBitmap.hpp"
#include "bitmap/TrophyGoldenBitmap.hpp"
#include "bitmap/flappyBird/FloorBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/flappyBird/FlappyBird.hpp"
#include "font/Fonts.hpp"
#include "display/DisplayManager.hpp"
#include <game/menu/Menu.hpp>
#include "eeprom/EepromManager.hpp"

FlappyBirdMenu::FlappyBirdMenu() 
{

}

void FlappyBirdMenu::renderMenu()
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-60, -1, 480, 250, skyBackgroundBitmap);
    backgroundSprite.pushImage(-60, 249, 480, 70, floorBitmap);
    backgroundSprite.pushSprite(60, 1);

    TFT_eSPI& display = DisplayManager::getDisplay();
    
    display.setTextColor(TFT_WHITE);
    //display.drawString("FlappyBird", 125, 40);
    DisplayManager::resetFont();
    display.setFreeFont(FF22);
    display.setTextSize(1);
    display.fillRoundRect(290, 135, 150, 40, 10, TFT_BLACK);
    display.fillRoundRect(290, 137, 148, 36, 10, 0xFEE0);
    display.fillRoundRect(130, 130, 180, 50, 10, TFT_DARKGREY);
    display.drawRoundRect(130, 130, 180, 50, 10, TFT_BLACK);
    display.drawRoundRect(131, 131, 178, 48, 8, TFT_BLACK);
    display.pushImage(310, 138, 35, 35, trophyGoldenBitmap);
    display.drawString("Easy", 184, 146);

    display.fillRoundRect(290, 195, 150, 40, 10, TFT_BLACK);
    display.fillRoundRect(290, 197, 148, 36, 10, 0xFEE0);
    display.fillRoundRect(130, 190, 180, 50, 10, TFT_DARKGREY);
    display.drawRoundRect(130, 60 + 130, 180, 50, 10, TFT_BLACK);
    display.drawRoundRect(131, 60 + 131, 178, 48, 8, TFT_BLACK);
    display.pushImage(310, 198, 35, 35, trophyGoldenBitmap);
    display.drawString("Normal", 172, 208);

    display.fillRoundRect(290, 255, 150, 40, 10, TFT_BLACK);
    display.fillRoundRect(290, 257, 148, 36, 10, 0xFEE0);
    display.fillRoundRect(130, 250, 180, 50, 10, TFT_DARKGREY);
    display.drawRoundRect(130, 120 + 130, 180, 50, 10, TFT_BLACK);
    display.drawRoundRect(131, 120 + 131, 178, 48, 8, TFT_BLACK);
    display.pushImage(310, 258, 35, 35, trophyGoldenBitmap);
    display.drawString("Fast", 187, 266);

    int highscores[] = {
        EepromManager::readInt16(EepromManager::EEPROM_FLAPPYBIRD_EASY_HIGHSCORE_ADDR_INT16),
        EepromManager::readInt16(EepromManager::EEPROM_FLAPPYBIRD_NORMAL_HIGHSCORE_ADDR_INT16),
        EepromManager::readInt16(EepromManager::EEPROM_FLAPPYBIRD_HARD_HIGHSCORE_ADDR_INT16)
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

    display.setTextColor(TFT_DARKGREY);
    display.setTextSize(1);
    display.setFreeFont(FF26);
    display.drawString(highscoreStrings[0], 364, 146);
    display.drawString(highscoreStrings[1], 364, 206);
    display.drawString(highscoreStrings[2], 364, 266);

    highlightSelectedButton();
    DisplayManager::resetFont();
}

void FlappyBirdMenu::update() 
{
    
}

void FlappyBirdMenu::advanceSelectionDown()
{
    unhighlightSelectedButton();
    upCountMenuIndex();
    highlightSelectedButton();
}

void FlappyBirdMenu::advanceSelectionUp()
{
    unhighlightSelectedButton();
    downCountMenuIndex();
    highlightSelectedButton();
}

void FlappyBirdMenu::unhighlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(130, menuIndex*60 + 130, 180, 50, 10, TFT_BLACK);
    display.drawRoundRect(131, menuIndex*60 + 131, 178, 48, 8, TFT_BLACK);
}

void FlappyBirdMenu::highlightSelectedButton() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRoundRect(130, menuIndex*60 + 130, 180, 50, 10, TFT_WHITE);
    display.drawRoundRect(131, menuIndex*60 + 131, 178, 48, 8, TFT_WHITE);
}

void FlappyBirdMenu::executeSelected()
{
    std::unique_ptr<Game> newGame(new FlappyBird(menuIndex));
    setCurrentGame(std::move(newGame));
}