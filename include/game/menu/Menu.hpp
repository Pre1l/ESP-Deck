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
        int menuButtonAmount;
        static int menuReturnIndex;

    public:
        Menu();
        void update() override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;
        void static drawMenuOutline(int x, int y, int width, int height, bool roundEdges, bool status);

    private:
        void advanceSelectionUpAndExecute();
        void advanceSelectionDownAndExecute();
        void downCountMenuIndex();
        void upCountMenuIndex();
        void unhighlightSelectedButton();
        void highlightSelectedButton();
};

#endif // MENU_HPP