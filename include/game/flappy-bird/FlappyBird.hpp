#ifndef FlappyBird_HPP
#define FlappyBird_HPP

#include "game/Game.hpp"
#include "game/flappy-bird/Pillar.hpp"
#include "game/flappy-bird/Bird.hpp"
#include <Arduino.h>
#include <random>
#include <list>
#include <String>
#include <eeprom/EepromManager.hpp>

class FlappyBird : public Game
{
    private:
        bool gameover;
        int spawnCounter;
        const float FIXED_TIMESTEP = 0.016f; // 16 Millisekunden
        float accumulatedTime = 0.0f;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> randomGap;
        std::uniform_int_distribution<> randomYPos;
        int pillarXSize;
        std::list<Pillar> pillars;
        Bird myBird;
        int speed;
        int score;
        int difficulty;
        int highscore;
        int spawnSpeed;
        int TapMessageYPos;
        int TapMessageXPos;
        bool upbutton;
        bool jumpRequest = false;
        String difficultyText;
        void updatePillars();
        void createPillar();
        void deletePillar();
        void startGame();
        void gameOver();
        void gameOverAnimation();
        void renderTAPMessage(int x, int y);
        void removeTAPMessage(int x, int y);
        bool checkCollision(Pillar& rect1, Bird& rect2);
        void updateScore();
        const int FlappyBirdHighscoreAddresses[3] = {
            EepromManager::EEPROM_FLAPPYBIRD_EASY_HIGHSCORE_ADDR_INT16, //4
            EepromManager::EEPROM_FLAPPYBIRD_NORMAL_HIGHSCORE_ADDR_INT16, //5
            EepromManager::EEPROM_FLAPPYBIRD_HARD_HIGHSCORE_ADDR_INT16 //6 01.06.2024
        };
        void updateHighscore();
        void onGameClosed();
    public:
        FlappyBird(int difficulty);
        ~FlappyBird() override;

        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void update(float deltaTime) override;
};


#endif