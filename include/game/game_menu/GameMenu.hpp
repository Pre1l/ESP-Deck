#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "game/Game.hpp"

class GameMenu : public Game
{
    private:
        bool focusOnSideMenu;

    public:
        GameMenu();
        void update();
        void keyPressed(int key) override;
        void keyReleased(int key) override;
};

#endif // GAMEMENU_HPP