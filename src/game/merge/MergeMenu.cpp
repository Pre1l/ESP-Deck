#include "game/merge/MergeMenu.hpp"

#include "bitmap/FactoryBackgroundBitmap.hpp"
#include "game/Game.hpp"
#include "game/merge/Merge.hpp"
#include "core/Core.hpp"
#include <font/Fonts.hpp>

MergeMenu::MergeMenu() 
{

}

void MergeMenu::renderMenu() 
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-60, -1, 480, 320, factoryBackgroundBitmap);
    backgroundSprite.pushSprite(60, 1);
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF32);
    display.setTextColor(0xFFFB);
    display.drawString("Merge", 125, 40);
    display.setFreeFont(FF29);
    display.setTextColor(0xFA85);
    display.drawString("2048", 125, 110);
    DisplayManager::resetFont();
    //display.fillRoundRect(310, 115, 100, 40, 10, 0xFEE0);
    display.fillRoundRect(160, 150, 180, 50, 10, TFT_DARKGREY);

    display.drawRoundRect(160, 150, 180, 50, 10, 0xFFFB);
    display.drawRoundRect(161, 151, 178, 48, 9, 0xFFFB);
    //display.pushImage(330, 118, 35, 35, trophyGoldenBitmap);
    display.drawString("Start", 210, 159);
}
 
void MergeMenu::update()
{

}

void MergeMenu::advanceSelectionDown() 
{

}

void MergeMenu::advanceSelectionUp() 
{

}

void MergeMenu::executeSelected() 
{
    std::unique_ptr<Game> newGame(new Merge());
    Core::setCurrentGame(std::move(newGame));
}