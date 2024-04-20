#ifndef SNAKE_MENU
#define SNAKE_MENU

#include "game/menu/GameMenu.hpp"

class SnakeMenu : public GameMenu 
{
    public:
        SnakeMenu();
        void renderMenu() override;
        void advanceSelectionUp() override;
        void advanceSelectionDown() override;
        void executeSelected() override;
};

#endif // SNAKE_MENU