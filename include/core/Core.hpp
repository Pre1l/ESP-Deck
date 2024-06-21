#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include <Arduino.h>
class Game;

namespace Core 
{
    extern TaskHandle_t core0TaskHandle;
    extern std::unique_ptr<Game> currentGame;
    extern bool menuButtonPressed;
    extern unsigned long previousMillis;
    extern const int RIGHT_PIN;
    extern const int UP_PIN;
    extern const int LEFT_PIN;
    extern const int DOWN_PIN;
    extern const int ACTION_PIN;
    extern const int MENU_PIN;
    extern int keyPins[];

    enum class Direction {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };

    enum class Key {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        ACTION
    };

    void inputLoop(void * parameter);
    void init();
    void run();
    void setCurrentGame(std::unique_ptr<Game> game);
}

#endif // CORE_HPP