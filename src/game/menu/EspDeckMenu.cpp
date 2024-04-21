#include "game/menu/EspDeckMenu.hpp"
#include "bitmaps/CityBackgroundBitmap.hpp"
#include "font/Fonts.hpp"

EspDeckMenu::EspDeckMenu() 
{

}

void EspDeckMenu::renderMenu()
{
    backgroundSprite.pushImage(0, 0, 480, 320, cityBackgroundBitmap);
    backgroundSprite.pushSprite(60, 1);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setTextColor(TFT_WHITE);
    display.setFreeFont(FF31);
    display.drawString("ESP-Deck", 105, 35);
    DisplayManager::resetFont();
    display.setTextSize(1);
    display.drawString("Update Build 23", 105, 95);
    DisplayManager::resetFont();
}

void EspDeckMenu::advanceSelectionDown()
{
    Serial.println("EspDeckMenu Down");
}

void EspDeckMenu::advanceSelectionUp()
{
    Serial.println("EspDeckMenu Up");
}

void EspDeckMenu::executeSelected()
{
    Serial.println("EspDeckMenu Execute");
}