#include "game/merge/MergeMenu.hpp"

#include "bitmap/FactoryBackgroundBitmap.hpp";
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
    setCurrentGame(std::move(newGame));
}