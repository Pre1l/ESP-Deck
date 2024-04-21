#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "display/DisplayManager.hpp"

class GameMenu 
{
    protected:
        static TFT_eSprite backgroundSprite;
        int menuIndex;
        int menuButtonAmount;

    public: 
        virtual void renderMenu() = 0;
        virtual void advanceSelectionUp() = 0;
        virtual void advanceSelectionDown() = 0;
        virtual void executeSelected() = 0;
        virtual const unsigned short* getIconBitmap() const = 0;

        static void init();

    protected:
        void downCountMenuIndex();
        void upCountMenuIndex();
};

#endif // GAMEMENU_HPP