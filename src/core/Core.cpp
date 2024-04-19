#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/Game.hpp"
#include "game/game_menu/GameMenu.hpp"
#include "game/snake/Snake.hpp"
#include "display/DisplayManager.hpp"
#include "TFT_eSPI.h"

#define right 9
#define up 10
#define left 11
#define down 12
#define action 13
#define menu 46

TaskHandle_t core0TaskHandle;
std::unique_ptr<Game> currentGame;
bool menuButtonPressed = true;

void setup() 
{
    Serial.begin(250000);

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
}

void loop()
{
    if (menuButtonPressed) {
        currentGame.reset(new Snake());
        menuButtonPressed = false;
    }

    currentGame->update();
}

void inputLoop(void * parameter)
{
    bool menuButtonSpamProt = true;

    for (;;) {
        if (!menuButtonPressed) {
            if (digitalRead(menu) == LOW && menuButtonSpamProt) {
                menuButtonPressed = true;
                menuButtonSpamProt = false;
            } else if (digitalRead(menu) == HIGH) {
                menuButtonSpamProt = true;
            }
            
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
            }
        }
        delay(50);
    }
}