#include "core/Core.hpp"
#include <Arduino.h>
#include <memory>
#include "game/Game.hpp"
#include "game/menu/Menu.hpp"
#include "game/snake/Snake.hpp"
#include "game/knight-game/KnightGameController.hpp"
#include "display/DisplayManager.hpp"
#include "TFT_eSPI.h"
#include <EEPROM.h>
#include <iostream>
#include <eeprom/EepromManager.hpp>

#define RIGHT_PIN 10
#define UP_PIN 11
#define LEFT_PIN 13
#define DOWN_PIN 12
#define ACTION_PIN 46
#define MENU_PIN 9
int keyPins[] = {RIGHT_PIN, UP_PIN, LEFT_PIN, DOWN_PIN, ACTION_PIN};

TaskHandle_t core0TaskHandle;
std::unique_ptr<Game> currentGame;
bool menuButtonPressed = true;
unsigned long previousMillis = 0;

void setup() 
{
    Serial.begin(250000);
    std::cout << "Starting..." << std::endl;

    EEPROM.begin(EepromManager::EEPROM_SIZE);

    xTaskCreatePinnedToCore(
        inputLoop,
        "Input",
        10000,
        NULL,
        1,
        &core0TaskHandle,
        0
    );

    pinMode(RIGHT_PIN, INPUT_PULLUP);
    pinMode(UP_PIN, INPUT_PULLUP);
    pinMode(LEFT_PIN, INPUT_PULLUP);
    pinMode(DOWN_PIN, INPUT_PULLUP);
    pinMode(ACTION_PIN, INPUT_PULLUP);
    pinMode(MENU_PIN, INPUT_PULLUP);

    randomSeed(analogRead(0));

    DisplayManager::initialize();

    if (EepromManager::readInt8(EepromManager::EEPROM_STATUS_ADDR_INT8) != 1) {
        std::cout << "Configurating EEPROM..." << std::endl;
        for (int i = 0; i < EepromManager::EEPROM_SIZE - 1; i++) {
            EepromManager::writeInt8(i, 0);
        }
        EepromManager::writeInt8(EepromManager::EEPROM_STATUS_ADDR_INT8, 1);
    }
    std::cout << "Setup Complete!" << std::endl;
}

void loop()
{
    if (menuButtonPressed) {
        if (!currentGame || currentGame->getGameType() != Game::GameType::MENU)
            currentGame.reset(new Menu());
        menuButtonPressed = false;
    }

    unsigned long currentMillis = millis();
    unsigned long deltaTime = currentMillis - previousMillis;

    currentGame->update(deltaTime);

    previousMillis = currentMillis;
}

void setCurrentGame(std::unique_ptr<Game> newGame) 
{
    currentGame = std::move(newGame);
}

void inputLoop(void * parameter)
{
    bool menuButtonSpamProt = true;
    bool keyStates[5] = {false};

    for (;;) {
        if (!menuButtonPressed) {
            if (digitalRead(MENU_PIN) == LOW && menuButtonSpamProt) {
                menuButtonPressed = true;
                menuButtonSpamProt = false;
            } else if (digitalRead(MENU_PIN) == HIGH) {
                menuButtonSpamProt = true;
            }
            
            for (int key = 0; key < 5; ++key) {
                int pin = keyPins[key];
                bool &keyState = keyStates[key];
                
                if (digitalRead(pin) == LOW && !keyState) {
                    currentGame->keyPressed(key);
                    keyState = true;
                } else if (digitalRead(pin) == HIGH && keyState) {
                    currentGame->keyReleased(key);
                    keyState = false;
                }
            }
        }
        delay(50);
    }
}