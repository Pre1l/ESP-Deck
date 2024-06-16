#ifndef Pillar_HPP
#define Pillar_HPP
#include <Arduino.h>
class Pillar {
private:
    int xPos;
    int yPos;
    int gap;
    int speed;
    int xSize;
    int ySize;
    int openingXSize;
    int openingYSize;
    bool devalued;
 
public:
    Pillar(int yPos, int gap, int speed, int xSize);
    void updatePillar();
    void gameOverAnimation();
    int getXPos();
    int getYPosAbove();
    int getYPosBelow();
    int getXSize();
    int getYSize();
    int redeemScorePoints();
};
#endif
