#ifndef LIGHTSOUTMENU_HPP
#define LIGHTSOUTMENU_HPP

#include "game/menu/GameMenu.hpp"
#include "bitmap/lightsOut/LightsOutIconBitmap.hpp"

class LightsOutMenu : public GameMenu 
{
    public:
        LightsOutMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        void update() override;
        const unsigned short* getIconBitmap() const override { return lightsOutIconBitmap; }

    private:
        void highlightSelectedButton();
        void unhighlightSelectedButton();
};

#endif 