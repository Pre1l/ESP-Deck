#include "game/menu/EspDeckMenu.hpp"
#include "bitmaps/CityBackgroundBitmap.hpp"

EspDeckMenu::EspDeckMenu() 
{

}

void EspDeckMenu::renderMenu()
{
    backgroundSprite.pushImage(0, 0, 480, 320, cityBackgroundBitmap);
    backgroundSprite.pushSprite(80, 0);
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