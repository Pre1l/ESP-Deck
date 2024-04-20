#ifndef ESP_DECK_MENU
#define ESP_DECK_MENU

#include "game/menu/GameMenu.hpp"

class EspDeckMenu : public GameMenu 
{
    public:
        EspDeckMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
};

#endif // ESP_DECK_MENU