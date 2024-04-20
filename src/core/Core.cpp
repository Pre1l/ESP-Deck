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
        currentGame.reset(new GameMenu());
        menuButtonPressed = false;
    }

    currentGame->update();
}

void inputLoop(void * parameter)
{
    bool menuButtonSpamProt = true;
    bool upKey = false;
    bool downKey = false;
    bool leftKey = false;
    bool rightKey = false;
    bool actionKey = false;

    for (;;) {
        if (!menuButtonPressed) {
            if (digitalRead(menu) == LOW && menuButtonSpamProt) {
                menuButtonPressed = true;
                menuButtonSpamProt = false;
            } else if (digitalRead(menu) == HIGH) {
                menuButtonSpamProt = true;
            }
            
            if (digitalRead(right) == LOW && !rightKey) {
                currentGame->keyPressed(0);
                rightKey = true;
            } else if (digitalRead(up) == LOW && !upKey) {
                currentGame->keyPressed(1);
                upKey = true;
            } else if (digitalRead(left) == LOW && !leftKey) {
                currentGame->keyPressed(2);
                leftKey = true;
            } else if (digitalRead(down) == LOW && !downKey) {
                currentGame->keyPressed(3);
                downKey = true;
            } else if (digitalRead(action) == LOW && !actionKey) {
                currentGame->keyPressed(4);
                actionKey = true;
            }

            if (digitalRead(right) == HIGH && rightKey) {
                currentGame->keyReleased(0);
                rightKey = false;
            }
            if (digitalRead(up) == HIGH && upKey) {
                currentGame->keyReleased(1);
                upKey = false;
            }
            if (digitalRead(left) == HIGH && leftKey) {
                currentGame->keyReleased(2);
                leftKey = false;
            }
            if (digitalRead(down) == HIGH && downKey) {
                currentGame->keyReleased(3);
                downKey = false;
            }
            if (digitalRead(action) == HIGH && actionKey) {
                currentGame->keyReleased(4);
                actionKey = false;
            }
        }
        delay(50);
    }
}