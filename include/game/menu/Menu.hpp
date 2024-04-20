#ifndef MENU_HPP
#define MENU_HPP

#include "game/Game.hpp"
#include <game/menu/GameMenu.hpp>
#include <vector>
#include <memory>

class Menu : public Game
{
    private:
        bool focusOnSideMenu;
        std::vector<std::unique_ptr<GameMenu>> gameMenus;
        int menuIndex;

    public:
        Menu(int menuIndex);
        void update() override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;
        int getSideMenuIndex() const override { return 0; };

    private:
        void advanceSelectionUpAndExecute();
        void advanceSelectionDownAndExecute();
};

#endif // MENU_HPP