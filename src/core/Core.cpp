#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/Game.hpp"
#include "game/GameMenu.hpp"
#include "game/Snake.hpp"
#include "display/DisplayManager.hpp"

#define right 9 // ORANGE
#define up 10   // GREEN
#define left 11 // BLUE
#define down 12 // YELLOW
#define action 43
#define menu 13 

TaskHandle_t core0TaskHandle;
std::unique_ptr<Game> currentGame;
bool menuButtonPressed = false;

void setup() 
{
    Serial.begin(115200);

    xTaskCreatePinnedToCore(
        inputLoop,
        "Input",
        10000,
        NULL,
        1,
        &core0TaskHandle,
        0
    );

    pinMode(right, INPUT_PULLUP);
    pinMode(up, INPUT_PULLUP);
    pinMode(left, INPUT_PULLUP);
    pinMode(down, INPUT_PULLUP);
    pinMode(action, INPUT_PULLUP);
    pinMode(menu, INPUT_PULLUP);

    randomSeed(analogRead(0));

    DisplayManager::initialize();

    currentGame.reset(new Snake());
}

void loop()
{
    if (menuButtonPressed) {
        currentGame.reset(new GameMenu());
        menuButtonPressed = false;
    }

    currentGame->update();
}

void inputLoop(void * parameter)
{
    for (;;) {
        if (digitalRead(right) == LOW) {
            currentGame->input(0);
        } else if (digitalRead(up) == LOW) {
            currentGame->input(1);
        } else if (digitalRead(left) == LOW) {
            currentGame->input(2);
        } else if (digitalRead(down) == LOW) {
            currentGame->input(3);
        } else if (digitalRead(action) == LOW) {
            currentGame->input(4);
        } else if (digitalRead(menu) == LOW) {
            menuButtonPressed = true;
        }
        delay(10);
    }
}