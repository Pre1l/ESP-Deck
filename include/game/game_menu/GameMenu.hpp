#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "game/Game.hpp"

class GameMenu : public Game
{
    public:
        GameMenu();
        void update();
        void input(int key);

    private:
        bool focusOnSideMenu;
};

#endif // GAMEMENU_HPP