#include "game/snake/SnakeMenu.hpp"
#include "bitmaps/GreenBrickBackgroundBitmap.hpp"
#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/snake/Snake.hpp"

SnakeMenu::SnakeMenu() 
{

}

void SnakeMenu::renderMenu()
{
    backgroundSprite.pushImage(-80, 0, 480, 320, greenBrickBackgroundBitmap);
    backgroundSprite.pushSprite(80, 0);
}

void SnakeMenu::advanceSelectionDown()
{
    Serial.println("SnakeMenu Down");
}

void SnakeMenu::advanceSelectionUp()
{
    Serial.println("SnakeMenu Up");
}

void SnakeMenu::executeSelected()
{
    DisplayManager::getDisplay().drawRect(80, 0, 400, 320, 0x18e3);
    std::unique_ptr<Game> newGame(new Snake());
    setCurrentGame(std::move(newGame));
}