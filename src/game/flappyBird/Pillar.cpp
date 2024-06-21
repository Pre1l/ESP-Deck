#include "game/flappy-bird/Pillar.hpp"
#include <TFT_eSPI.h>
#include "display/DisplayManager.hpp"
#include "bitmap/flappy-bird/SkyBackgroundBitmap.hpp"

Pillar::Pillar(int yPos, int gap, int speed, int xSize) 
: xPos(480),
  yPos(yPos),
  xSize(xSize),//58
  ySize(200),
  gap(gap),
  speed(speed),
  devalued(false),
  openingXSize(xSize + 6),
  openingYSize(15)
{
   
}

void Pillar::updatePillar()
{
    xPos -= speed;
    DisplayManager::getDisplay().fillRect(xPos + 1, yPos - ySize - gap - openingYSize + 1, xSize -2, ySize-1, DisplayManager::tft.color565(7, 219, 64));//Oben
    DisplayManager::getDisplay().drawRect(xPos, yPos - ySize - gap - openingYSize, xSize, ySize+1, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos + xSize, yPos - ySize - gap - openingYSize, xPos + xSize, yPos - ySize - gap - openingYSize, speed, ySize, 480, 320, skyBackgroundBitmap);

    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2) + 1, yPos - gap - openingYSize + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos - gap - openingYSize , openingXSize, openingYSize, DisplayManager::tft.color565(0, 0, 0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos - gap - openingYSize , xPos - ((openingXSize - xSize) / 2) + openingXSize ,  yPos - gap - openingYSize, speed, openingYSize, 480, 320, skyBackgroundBitmap);
   
    DisplayManager::getDisplay().fillRect(xPos + 1, yPos + gap + openingYSize, xSize-2, 250 - yPos - gap - openingYSize, DisplayManager::tft.color565(7, 219, 64));//Unten 
    DisplayManager::getDisplay().drawRect(xPos, yPos + gap + openingYSize-1, xSize, 250 - yPos - gap - openingYSize+2, DisplayManager::tft.color565(0, 0, 0));
    DisplayManager::renderPartialBitmap(xPos + xSize, yPos + gap + openingYSize-1, xPos + xSize, yPos + gap + openingYSize-1, speed, 250 - yPos - gap - openingYSize +1, 480, 320, skyBackgroundBitmap);

    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2)+1, yPos + gap + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos + gap, openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos + gap ,xPos - ((openingXSize - xSize) / 2) + openingXSize, yPos + gap , speed, openingYSize, 480, 320, skyBackgroundBitmap);
   
}
void Pillar::gameOverAnimation()
{
    delay(5);
    gap += 1;
    DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2) + 1, yPos - gap - openingYSize + 1, openingXSize -2, openingYSize -2, DisplayManager::tft.color565(7, 219, 64));
    DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos - gap - openingYSize , openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
    DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos - gap, xPos - ((openingXSize-xSize)/2) , yPos - gap, openingXSize, 2 , 480, 320, skyBackgroundBitmap);

    if (yPos + gap + openingYSize <= 251) {
        DisplayManager::tft.fillRect(xPos - ((openingXSize-xSize)/2)+1, yPos + gap + 1, openingXSize -2, openingYSize - 2, DisplayManager::tft.color565(7, 219, 64));
        DisplayManager::tft.drawRect(xPos - ((openingXSize-xSize)/2), yPos + gap, openingXSize, openingYSize, DisplayManager::tft.color565(0,0,0));
        DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos + gap - 2, xPos - ((openingXSize-xSize)/2) , yPos + gap -2, openingXSize, 2 , 480, 320, skyBackgroundBitmap);
    } else if (yPos + gap <= 251) {
        DisplayManager::renderPartialBitmap(xPos - ((openingXSize-xSize)/2), yPos + gap - 2, xPos - ((openingXSize-xSize)/2) , yPos + gap -2, openingXSize, 2 , 480, 320, skyBackgroundBitmap);
        DisplayManager::tft.drawFastHLine(xPos - ((openingXSize-xSize)/2), yPos + gap -1, openingXSize, TFT_BLACK);
    }
}

int Pillar::redeemScorePoints()
{
    if (devalued == false) {
        devalued = true;
        return 1;
    }
    return 0;
}

int Pillar::getXPos(){
    return xPos;
}

int Pillar::getYPosAbove(){
    return yPos - gap;
}

int Pillar::getYPosBelow(){
    return yPos + gap;
}

int Pillar::getXSize(){
    return xSize;
}

int Pillar::getYSize(){
    return ySize;
}


