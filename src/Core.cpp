#include "Core.hpp"
#include <Arduino.h>
#include "Snake.hpp"
#include "DisplayManager.hpp"

#define right 9 // ORANGE
#define up 10   // GREEN
#define left 11 // BLUE
#define down 12 // YELLOW

TaskHandle_t core0TaskHandle;

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
    Snake::initialize();    
}

void loop()
{
    if (!Snake::gameOver) {
        delay(1.5 * (120 - Snake::snakeTiles.size()) + 200);
        Snake::update();
    }
}

void inputLoop(void * parameter) 
{
    for (;;) {
        if (digitalRead(right) == LOW && Snake::lastMovedDirection != 2) {
            Snake::direction = 0;
        } else if (digitalRead(up) == LOW && Snake::lastMovedDirection != 3) {
            Snake::direction = 1;
        } else if (digitalRead(left) == LOW && Snake::lastMovedDirection != 0) {
            Snake::direction = 2;
        } else if (digitalRead(down) == LOW && Snake::lastMovedDirection != 1) {
            Snake::direction = 3;
        }
        delay(10);
    }
}