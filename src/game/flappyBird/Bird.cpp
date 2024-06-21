#include "game/flappy-bird/Bird.hpp"
#include <TFT_eSPI.h> 
#include "bitmap/flappy-bird/BirdBitmap.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/flappy-bird/SkyBackgroundBitmap.hpp"

Bird::Bird(float gravity, float maxFallSpeed, float jumpHeight) 
: yPos(120),
  xPos(40),
  xSize(38),
  ySize(28),
  speed(0),
  currentSpeed(0),
  gravity(gravity),
  maxFallSpeed(maxFallSpeed),
  jumpHeight(jumpHeight),
  animation(0)
{

}

void Bird::update(float deltaTime)
{
    currentSpeed = speed;

    if (speed > - maxFallSpeed) {
        speed = speed - gravity;
    }

    yPos = yPos - currentSpeed;
    
    renderFlappyBird();
    delay(2);
}

void Bird::renderFlappyBird() 
{
    std::vector<unsigned short> partialBackgroundVector(extractPartialBackground(xPos, yPos, xSize, ySize));
    std::vector<unsigned short> birdVector(birdBitmap, birdBitmap + ySize * xSize); //von Zeiger bis zu (Zeiger + 1064)
    std::vector<unsigned short> birdTrailVector;
    std::vector<unsigned short> resultVector;
    
    for (int i = 0; i < birdVector.size(); i++) {
        if (birdVector[i] == 0x7639) {
            birdVector[i] = partialBackgroundVector[i];
        }
    }
    resultVector.insert(resultVector.end(), birdVector.begin(), birdVector.end());
   
    if (currentSpeed > 0) {
        birdTrailVector = extractPartialBackground(xPos, yPos + ySize, xSize, currentSpeed);
        resultVector.insert(resultVector.end(), birdTrailVector.begin(), birdTrailVector.end());
        TFT_eSprite sprite = TFT_eSprite(&DisplayManager::getDisplay());
        sprite.createSprite(xSize, ySize + currentSpeed);
        sprite.setSwapBytes(true);
        sprite.pushImage(0, 0, xSize, ySize + currentSpeed, resultVector.data());
        sprite.pushSprite(xPos, yPos);
        sprite.deleteSprite();
        //DisplayManager::getDisplay().pushImage(xPos, yPos, xSize, ySize + currentSpeed, resultVector.data());
    } else if (currentSpeed <= 0) {
        birdTrailVector = extractPartialBackground(xPos, yPos - currentSpeed  * - 1, xSize, currentSpeed  * - 1);
        resultVector.insert(resultVector.begin(), birdTrailVector.begin(), birdTrailVector.end());

        TFT_eSprite sprite = TFT_eSprite(&DisplayManager::getDisplay());
        sprite.createSprite(xSize, ySize + currentSpeed * - 1);
        sprite.setSwapBytes(true);
        sprite.pushImage(0, 0, xSize, ySize + currentSpeed * - 1, resultVector.data());
        sprite.pushSprite(xPos, yPos - currentSpeed * -1);
        sprite.deleteSprite();
        //DisplayManager::getDisplay().pushImage(xPos, yPos - currentSpeed * -1, xSize, ySize + currentSpeed * -1, resultVector.data());
    }
}

std::vector<unsigned short> Bird::extractPartialBackground(int xPartialBitmap, int yPartialBitmap, int widthPartialBitmap, int heightPartialBitmap)
{
    std::vector<unsigned short> partialBackgroundVector;
    int index = yPartialBitmap * 480 + xPartialBitmap;//Start

    for (int row = 0; row < heightPartialBitmap; row++) {
        
        partialBackgroundVector.insert(partialBackgroundVector.end(), skyBackgroundBitmap + index, skyBackgroundBitmap + index + widthPartialBitmap);//Zeilenweise 
        index += 480;
    }
    return partialBackgroundVector;
}

void Bird::gameOverAnimation()
{
    animation++;
    if(yPos < 119) {
        yPos++;
        if (yPos < 0 - ySize) {
            yPos = 120;
        }
        currentSpeed = -1;
        renderFlappyBird();
        
    } else if (yPos > 121) {
        yPos--;
        if (yPos < 250 - ySize) {
            currentSpeed = 1;
            renderFlappyBird();
        }
    } else {
        renderFlappyBird();
    }
    
}

void Bird::jump()
{
    speed = jumpHeight;
}

int Bird::getYPos()
{
    return yPos;
}

int Bird::getXPos()
{
    return xPos;
}

int Bird::getYSize()
{
    return ySize;
}

int Bird::getXSize()
{
    return xSize;
}