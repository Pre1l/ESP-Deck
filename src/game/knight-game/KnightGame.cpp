#include "game/knight-game/KnightGame.hpp"

#include <TFT_eSPI.h>
#include <display/DisplayManager.hpp>

KnightGame::KnightGame() 
{
    knightWalkSpriteSheet.createSprite(54, 64);
    knightWalkSpriteSheet.setSwapBytes(true);
    Knight knight();
}

void KnightGame::update(float deltaTime)  
{
    knight.update(deltaTime);
}

void KnightGame::keyPressed(int key) 
{
    switch (key) {
        case 0: knight.setState(knight.RUNNING_RIGHT); break;
        case 1: knight.setState(knight.IDLE); break; 
        case 2: knight.setState(knight.RUNNING_LEFT); break;
    }
}

void KnightGame::keyReleased(int key) 
{

}

void KnightGame::onGameClosed() 
{

}