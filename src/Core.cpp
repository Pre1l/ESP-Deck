#include "Core.hpp"
#include <Arduino.h>
#include "Game.hpp"
#include "Snake.hpp"
#include "DisplayManager.hpp"

#define right 9 // ORANGE
#define up 10   // GREEN
#define left 11 // BLUE
#define down 12 // YELLOW

TaskHandle_t core0TaskHandle;
Game* currentGame;

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

    randomSeed(analogRead(0));

    DisplayManager::initialize();

    currentGame = new Snake();
}

void loop()
{
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
        }
        delay(10);
    }
}