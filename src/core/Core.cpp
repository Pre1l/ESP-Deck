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

void setup() 
{
    Core::init();
}

void loop() 
{
    Core::run();
}

namespace Core 
{
    TaskHandle_t core0TaskHandle;
    std::unique_ptr<Game> currentGame;
    bool menuButtonPressed;
    unsigned long previousMillis;
    
    const int RIGHT_PIN = 10;
    const int UP_PIN = 11;
    const int LEFT_PIN = 13;
    const int DOWN_PIN = 12;
    const int ACTION_PIN = 46;
    const int MENU_PIN = 9;

    int keyPins[] = {RIGHT_PIN, UP_PIN, LEFT_PIN, DOWN_PIN, ACTION_PIN};

    void init() 
    {
        // Serial.begin();
        // std::cout << "Starting..." << std::endl;

        EEPROM.begin(EepromManager::EEPROM_SIZE);

        menuButtonPressed = true;
        previousMillis = 0;
        
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
            // std::cout << "Configurating EEPROM..." << std::endl;
            for (int i = 0; i < EepromManager::EEPROM_SIZE - 1; i++) {
                EepromManager::writeInt8(i, 0);
            }
            EepromManager::writeInt8(EepromManager::EEPROM_STATUS_ADDR_INT8, 1);
        }
        // std::cout << "Setup Complete!" << std::endl;
    }

    void run()
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
        Key keys[] {
            Key::RIGHT,
            Key::UP,
            Key::LEFT,
            Key::DOWN,
            Key::ACTION
        };

        for (;;) {
            if (!menuButtonPressed) {
                if (digitalRead(MENU_PIN) == LOW && menuButtonSpamProt) {
                    menuButtonPressed = true;
                    menuButtonSpamProt = false;
                } else if (digitalRead(MENU_PIN) == HIGH) {
                    menuButtonSpamProt = true;
                }
                
                for (int keyIndex = 0; keyIndex < 5; ++keyIndex) {
                    int pin = keyPins[keyIndex];
                    bool &keyState = keyStates[keyIndex];
                    
                    if (digitalRead(pin) == LOW && !keyState) {
                        currentGame->keyPressed(keys[keyIndex]);
                        keyState = true;
                    } else if (digitalRead(pin) == HIGH && keyState) {
                        currentGame->keyReleased(keys[keyIndex]);
                        keyState = false;
                    }
                }
            }
            delay(50);
        }
    }
}