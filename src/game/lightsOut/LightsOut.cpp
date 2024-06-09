#include "game/lightsOut/LightsOut.hpp"
#include "bitmap/lightsOut/LightsOutBackgroundBitmap.hpp"
#include "display/DisplayManager.hpp"
#include "font/Fonts.hpp"
#include <TFT_eSPI.h>

#include <stdlib.h>
#include <time.h>
#include <String>

LightsOut::LightsOut(int difficulty):
    gameOver(false),
    moves(0),
    cursorX(2),
    cursorY(2)
{   
    DisplayManager::resetFont();
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setFreeFont(FF32);
    display.setTextSize(1);
    display.setTextColor(TFT_WHITE);
    rows = 5;
    cols = 5;
    tileSize = 58;
    gap = 2;                                            
    edge =  9;
    lights.resize(rows, std::vector<bool>(cols, false));
    display.pushImage(0, 0, 480, 320, lightsOutBackgroundBitmap);
    display.fillRect(edge, edge, 302, 302, TFT_DARKGREY);
    
    switch (difficulty)
    {
    case 0:
        minCount = 4;
        maxCount = 4;
        difficultyText = "easy";
        break;
    case 1:
        minCount = 100;
        maxCount = 100;
        difficultyText = "difficult";
        break;
    
    default:
        break;
    }
    
    display.drawString(difficultyText, 310, 70);
    createGame();
   
}
void LightsOut::createGame()
{
    moves = 0;
    updateMoves();
    hideSolved();
    TFT_eSPI& display = DisplayManager::getDisplay();
    for(int i = 0; i < lights.size(); i++)
    {
        for(int j = 0; j < lights[i].size(); j++)
        {
            lights[i][j] = false;
            display.fillRect((i) * (gap + tileSize) + gap + edge, (j) * (gap + tileSize) + gap + edge, tileSize, tileSize, TFT_BLACK);
        }
    }
    moveCursor(cursorX, cursorY);
    srand(time(nullptr));
    
    for (int i = rand() % (maxCount - minCount + 1) + minCount; i > 0; i--)
    {
        invertAllPossibleOnes(rand() % 5, rand() % 5, display);
    }
}
void LightsOut::moveCursor(int xIndex, int yIndex)
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawRect((cursorX) * (tileSize + gap)  + gap + edge - gap, (cursorY) * (tileSize + gap)  + gap + edge - gap,tileSize + gap*2, tileSize + gap*2, TFT_DARKGREY);
    display.drawRect((cursorX) * (tileSize + gap)  + gap + edge - gap + 1, (cursorY) * (tileSize + gap)  + gap + edge - gap + 1, tileSize + gap*2 - 2, tileSize + gap*2 - 2, TFT_DARKGREY);

    cursorX = xIndex;
    cursorY = yIndex;

    display.drawRect((xIndex) * (tileSize + gap)  + gap + edge - gap, (yIndex) * (tileSize + gap)  + gap + edge - gap,tileSize + gap*2, tileSize + gap*2, TFT_RED);
    display.drawRect((xIndex) * (tileSize + gap)  + gap + edge - gap + 1, (yIndex) * (tileSize + gap)  + gap + edge - gap + 1, tileSize + gap*2 - 2, tileSize + gap*2 - 2, TFT_RED);
}
void LightsOut::invertOne(int xIndex, int yIndex, TFT_eSPI& display)
{
    
    
    if(lights[xIndex][yIndex] == false)
    {
        display.fillRect((xIndex) * (gap + tileSize) + gap + edge, (yIndex) * (gap + tileSize) + gap + edge, tileSize, tileSize, TFT_WHITE);
        lights[xIndex][yIndex] = true;
    }
    else{
        display.fillRect((xIndex) * (gap + tileSize) + gap + edge, (yIndex) * (gap + tileSize) + gap + edge, tileSize, tileSize, TFT_BLACK);
        lights[xIndex][yIndex] = false;
    }
}
void LightsOut::checkWin()
{
    for (int i = 0; i < lights.size(); i++)
    {
        for(int j = 0; j < lights[i].size(); j++)
        {
            if (lights[i][j] == true)
            {
                return;
            }
        }
    }
    gameOver = true;
    showSolved();
}
void LightsOut::update(float deltaTime) 
{
    
}
void LightsOut::invertAllPossibleOnes(int xIndex, int yIndex, TFT_eSPI& display)
{
    invertOne(xIndex, yIndex, display);
    if(xIndex + 1 < cols)
        invertOne(xIndex + 1, yIndex, display);
    if(xIndex -1 > -1)
        invertOne(xIndex -1, yIndex, display);
    if(yIndex + 1 < rows)
        invertOne(xIndex, yIndex + 1, display);
    if(yIndex -1 > -1)
        invertOne(xIndex, yIndex - 1, display);
}
void LightsOut::keyPressed(int key) 
{
    if(gameOver == false)
    {
        switch (key)
        {
        case 1: //Up
            if(cursorY > 0)
                moveCursor(cursorX, cursorY - 1);
            break;
        case 3: //Down
            if(cursorY < rows - 1)
                moveCursor(cursorX, cursorY +1);
            break;
        case 0: //Right
            if(cursorX < cols - 1)
                moveCursor(cursorX + 1, cursorY);
            break;
        case 2: //Left
            if(cursorX > 0)
                moveCursor(cursorX - 1, cursorY);
            break;
        case 4: //action
                moves++;
                updateMoves();
                TFT_eSPI& display = DisplayManager::getDisplay();
                invertAllPossibleOnes(cursorX, cursorY, display);
                checkWin();
            break;
        
        }
    }else{
        gameOver = false;
        createGame();
    }
}
void LightsOut::showSolved()
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.drawString("solved", 320, 125);
}
void LightsOut::hideSolved()
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.fillRect(320,125,170,40, TFT_BLACK);
}
void LightsOut::updateMoves()
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.fillRect(320,20,120,40, TFT_BLACK);
    display.drawString(String(moves), 320, 20);
}
void LightsOut::keyReleased(int key) 
{

}
void LightsOut::onGameClosed() 
{
    DisplayManager::resetFont();
}