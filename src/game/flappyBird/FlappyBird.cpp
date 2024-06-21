#include "game/flappy-bird/flappyBird.hpp"
#include "display/DisplayManager.hpp"
#include "bitmap/flappy-bird/FloorBitmap.hpp"
#include "bitmap/flappy-bird/SkyBackgroundBitmap.hpp"
#include "bitmap/flappy-bird/MessageBitmap.hpp"
#include <TFT_eSPI.h>
#include <list>
#include <random>
#include <string>
#include <chrono>
#include <thread>

const std::chrono::duration<double, std::ratio<1, 55>> target_frame_duration(1);

FlappyBird::FlappyBird(int difficulty)
: gen(rd()),
  gameover(true),
  spawnCounter(0),
  myBird(0.2, 10, 5),
  score(0),
  TapMessageXPos(180), 
  TapMessageYPos(185),
  difficulty(difficulty)
{   
    switch (difficulty)
    {
        case 0:
            myBird = Bird(0.2, 5, 5);
            randomGap = std::uniform_int_distribution<>(70, 80);
            randomYPos = std::uniform_int_distribution<>(95, 155);
            pillarXSize = 58;
            speed = 2;
            spawnSpeed = 150;
            difficultyText = "Easy";
            break;
        case 1:
            myBird = Bird(0.2, 10, 5);
            randomGap = std::uniform_int_distribution<>(50, 70);
            randomYPos = std::uniform_int_distribution<>(95, 155);
            pillarXSize = 58;
            speed = 4;
            spawnSpeed = 70;
            difficultyText = "Normal";
            break;
        case 2:
            myBird = Bird(0.4, 15, 6);
            randomGap = std::uniform_int_distribution<>(40, 60);
            randomYPos = std::uniform_int_distribution<>(75, 175);
            pillarXSize = 40;
            speed = 9;
            spawnSpeed = 40;
            difficultyText = "Fast";
            break;
        
        default:
            break;
    }
    highscore = EepromManager::readInt16(FlappyBirdHighscoreAddresses[difficulty]);
    
    DisplayManager::getDisplay().setTextSize(1);
    DisplayManager::getDisplay().setTextColor(TFT_DARKGREY);//DisplayManager::tft.color565(6, 220, 0)
    
    DisplayManager::getDisplay().pushImage(0, 0, 480, 250, skyBackgroundBitmap);
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, floorBitmap);
    myBird.renderFlappyBird();
    updateScore();
    updateHighscore();
    renderTAPMessage(TapMessageXPos, TapMessageYPos);
}

FlappyBird::~FlappyBird() 
{
    onGameClosed();
}

void FlappyBird::update(float deltaTime) 
{
    auto startTime = std::chrono::steady_clock::now();

    if (!gameover) {
        myBird.update(deltaTime);
        updatePillars();
        createPillar();
        deletePillar();

        Pillar& pillar = pillars.front();
        if (pillar.getXPos() + pillar.getXSize() <= myBird.getXPos() + myBird.getXSize() && pillar.getXPos() + pillar.getXSize() >= myBird.getXPos() + myBird.getXSize() - 10){
            
            score += pillar.redeemScorePoints();
            updateScore();
        }

        if(myBird.getYPos() >= 250 - myBird.getYSize() && gameover != true || pillars.size() != 0 && checkCollision(pillar, myBird))
            gameOver();
    } else {  
        if (upbutton && gameover)
            startGame();
    }

    auto endTime = std::chrono::steady_clock::now();
    auto update_duration = endTime - startTime;
    if (update_duration < target_frame_duration)
        std::this_thread::sleep_for(target_frame_duration - update_duration);
}
void FlappyBird::gameOver()
{
    gameover = true;
    //DisplayManager::getDisplay().drawString("-GAME OVER-", 170, 290);
    DisplayManager::getDisplay().pushImage(0, 250, 480, 70, floorBitmap);
   //DisplayManager::getDisplay().pushImage(170, 279, 192, 42, gameoverBitmap);
   
    updateScore();
    updateHighscore();
    gameOverAnimation();
    pillars.clear();
}

void FlappyBird::gameOverAnimation()
{
    delay(1500);
    for(int i = 0; i < 125; i ++)
    {
        myBird.gameOverAnimation();
        for (auto& pillar : pillars) 
        {
            pillar.gameOverAnimation();
        }
    }
    renderTAPMessage(TapMessageXPos, TapMessageYPos);
}

void FlappyBird::updateScore()
{
    DisplayManager::getDisplay().fillRect(405, 290, 60, 15, 0xDEB2);
    DisplayManager::getDisplay().drawString(("Score: " + std::to_string(score)).c_str(),350,290);
}

void FlappyBird::updateHighscore() 
{
    if (score > highscore) {
        
        EepromManager::writeInt16(FlappyBirdHighscoreAddresses[difficulty], score);
        highscore = score;
    }
    DisplayManager::getDisplay().fillRect(70, 290, 60, 15, 0xDEB2);
    DisplayManager::getDisplay().drawString(difficultyText + ": " + String(highscore), 20, 290);
}

void FlappyBird::updatePillars() {
    for (auto& pillar : pillars) {
        pillar.updatePillar();
    }
}

void FlappyBird::createPillar() {
   
    spawnCounter++;
    if (spawnCounter % spawnSpeed == 0)
        pillars.push_back(Pillar(randomYPos(gen), randomGap(gen), speed, pillarXSize)); 
}

void FlappyBird::deletePillar()
{
    for (auto& pillar : pillars) {
        if(pillar.getXPos() < -60)
        {
            pillars.pop_front();
        }
    }
}

void FlappyBird::startGame()
{
    gameover = false;
    spawnCounter = 0;
    score = 0;  
    removeTAPMessage(TapMessageXPos, TapMessageYPos);
    updateScore();
}

void FlappyBird::renderTAPMessage(int x, int y)
{
    int xS = 114;
    int yS = 36;
    
    std::vector<unsigned short> partialBackgroundVector;
    std::vector<unsigned short> messageVector(messageBitmap, messageBitmap + yS * xS); //von Zeiger bis zu (Zeiger + 1064)

    int index = y * 480 + x;//Start

    for (int row = 0; row < yS; row++) { 
        partialBackgroundVector.insert(partialBackgroundVector.end(), skyBackgroundBitmap + index, skyBackgroundBitmap + index + xS);//Zeilenweise 
        index += 480;
    }
    for (int i = 0; i < messageVector.size(); i++) {
        if (messageVector[i] == 0x7639) {
            messageVector[i] = partialBackgroundVector[i];
        }
    }                 
    //DisplayManager::getDisplay().drawString("                          ", 170, 290);
    DisplayManager::getDisplay().pushImage(x, y, xS, yS, messageVector.data());
}

void FlappyBird::removeTAPMessage(int x, int y)
{
    int xS = 114;
    int yS = 36;
    
    std::vector<unsigned short> partialBackgroundVector;

    int index = y * 480 + x;//Start

    for (int row = 0; row < yS; row++) {
        partialBackgroundVector.insert(partialBackgroundVector.end(), skyBackgroundBitmap + index, skyBackgroundBitmap + index + xS);//Zeilenweise 
        index += 480;
    }
    DisplayManager::getDisplay().pushImage(x, y, xS, yS, partialBackgroundVector.data());
}

void FlappyBird::keyPressed(Core::Key key)
{
    if(key == Core::Key::UP) {
        myBird.jump();
        upbutton = true;
    }
}

void FlappyBird::keyReleased(Core::Key key)
{
    if(key == Core::Key::UP) {
        upbutton = false; 
    }
}

bool FlappyBird::checkCollision(Pillar& rect1,  Bird& rect2) {
    
    if (rect2.getXPos() > rect1.getXPos() + rect1.getXSize() ||// rect1 liegt links von rect2
        rect2.getXPos() + rect2.getXSize() < rect1.getXPos() || // rect2 liegt links von rect1
        rect2.getYPos() > rect1.getYPosAbove() && rect2.getYPos() + rect2.getYSize() < rect1.getYPosBelow())   
    {
        return false;
    }
    return true;
}

void FlappyBird::onGameClosed()
{
    if(score > highscore) {
        EepromManager::writeInt16(FlappyBirdHighscoreAddresses[difficulty], score);
    }
}