#ifndef KNIGHT_MENU_HPP
#define KNIGHT_MENU_HPP

#include "game/menu/GameMenu.hpp"
#include "bitmap/knight-game/KnightIconBitmap.hpp"

class KnightMenu : public GameMenu 
{
    public:
        KnightMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        void update() override;
        const unsigned short* getIconBitmap() const override { return knightIconBitmap; }

    private:
        void highlightSelectedButton();
        void unhighlightSelectedButton();
};

#endif // KNIGHT_MENU_HPP