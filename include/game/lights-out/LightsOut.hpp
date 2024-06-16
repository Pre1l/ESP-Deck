#ifndef LIGHTSOUT_HPP
#define LIGHTSOUT_HPP

#include "game/Game.hpp"
#include <Arduino.h>
#include <vector>

#include <TFT_eSPI.h>
class LightsOut : public Game
{
    private:
        bool gameOver;
        int moves;
        int cursorX;
        int cursorY;
        int rows;
        int cols;
        int tileSize;
        int gap;
        int edge;
        int minCount;
        int maxCount;
        String difficultyText;
        std::vector<std::vector<bool>> lights;

    public:
        LightsOut(int difficulty);
        ~LightsOut();

        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void update(float deltaTime) override;

    private:
        void createGame();
        void moveCursor(int xIndex, int yIndex);
        void invertOne(int xIndex, int yIndex, TFT_eSPI& display);
        void invertAllPossibleOnes(int xIndex, int yIndex, TFT_eSPI& display);
        void checkWin();
        void showSolved();
        void hideSolved();
        void updateMoves();
        void onGameClosed();
};


#endif