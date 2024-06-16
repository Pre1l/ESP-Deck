#ifndef FLAPPYBIRDMENU_HPP
#define FLAPPYBIRDMENU_HPP

#include "game/menu/GameMenu.hpp"
#include "bitmap/flappy-bird/FlappyBirdIconBitmap.hpp"

class FlappyBirdMenu : public GameMenu 
{
    public:
        FlappyBirdMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        void update() override;
        const unsigned short* getIconBitmap() const override { return flappyBirdIconBitmap; }

    private:
        void highlightSelectedButton();
        void unhighlightSelectedButton();
};

#endif 