#ifndef ESP_DECK_MENU
#define ESP_DECK_MENU

#include "game/menu/GameMenu.hpp"
#include "bitmaps/EspDeckIconBitmap.hpp"

class EspDeckMenu : public GameMenu 
{
    public:
        EspDeckMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
        const unsigned short* getIconBitmap() const override { return espDeckIconBitmap; }
};

#endif // ESP_DECK_MENU