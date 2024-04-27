#include "game/merge/MergeMenu.hpp"

#include "bitmap/FactoryBackgroundBitmap.hpp";
#include "game/Game.hpp"
#include "game/merge/Merge.hpp"
#include "core/Core.hpp"

MergeMenu::MergeMenu() 
{

}

void MergeMenu::renderMenu() 
{
    menuIndex = 0;
    menuButtonAmount = 3;

    backgroundSprite.pushImage(-60, -1, 480, 320, factoryBackgroundBitmap);
    backgroundSprite.pushSprite(60, 1);
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