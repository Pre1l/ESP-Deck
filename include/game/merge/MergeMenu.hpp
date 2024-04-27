#ifndef MERGE_MENU_HPP
#define MERGE_MENU_HPP

#include "game/menu/GameMenu.hpp"
#include "bitmap/MergeIconBitmap.hpp"

class MergeMenu : public GameMenu
{
    public:
        MergeMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        void update() override;
        const unsigned short* getIconBitmap() const override { return mergeIconBitmap; }
};

#endif // MERGE_MENU_HPP