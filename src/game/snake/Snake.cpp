#include "game/snake/Snake.hpp"
#include "display/DisplayManager.hpp"
#include <ctime>
#include "bitmaps/SnakeBitmap.hpp"
#include "bitmaps/AppleBitmap.hpp"
#include "bitmaps/GreenBrickBackgroundBitmap.hpp"
#include "bitmaps/TrophyBitmap.hpp"
#include <EEPROM.h>
#include "config/eepromConfig.hpp"

Snake::Snake()
{
    direction = 0;
    lastMovedDirection = 0;
    gameOver = false;
    highscore = EEPROM.read(EEPROM_HIGHSCORE_ADDR);

    DisplayManager::getDisplay().setSwapBytes(true);
    DisplayManager::getDisplay().pushImage(0, 0, 480, 320, greenBrickBackgroundBitmap);

    DisplayManager::getDisplay().fillRoundRect(375, 10, 100, 40, 10, 0x3366);
    DisplayManager::getDisplay().pushImage(377, 15, 30, 30, appleBitmap);

    DisplayManager::getDisplay().fillRoundRect(375, 270, 100, 40, 10, 0x3366);
    DisplayManager::getDisplay().pushImage(375, 272, 35, 35, trophyBitmap);
    DisplayManager::getDisplay().setTextColor(0xF480);

    DisplayManager::getDisplay().fillRoundRect(410, 270, 65, 40, 10, 0x3366);
    String highscoreString = String(highscore);
    if (highscore < 10) {
        highscoreString = "00" + highscoreString;
    } else if (highscore < 100) {
        highscoreString = "0" + highscoreString;
    }
    DisplayManager::getDisplay().drawString(highscoreString, 408, 275);

    snakeSpriteSheet.createSprite(30, 30);
    snakeSpriteSheet.setSwapBytes(true);

    for (int row = 0; row < gridY; row++) {
        for (int col = 0; col < gridX; col++) {
            tiles[row][col] = 0;
            DisplayManager::getDisplay().fillRect(col * tileSize + offsetX, row * tileSize + offsetY, tileSize, tileSize, TFT_BLACK); 
        }
    }

    std::vector<Vector2D> randomSnakeTiles;

    for (int row = 0; row < gridY; row++) {
        for (int col = 3; col < gridX - 6; col++) {
            randomSnakeTiles.push_back(Vector2D(col, row));
        }
    }

    int randomTileIndex = random(randomSnakeTiles.size());
    Vector2D spawnSnakeTile1 = randomSnakeTiles[randomTileIndex];
    Vector2D spawnSnakeTile2 = spawnSnakeTile1.copy().subtractX(1);
    Vector2D spawnSnakeTile3 = spawnSnakeTile2.copy().subtractX(1);
    setStatus(spawnSnakeTile1, 1);
    setStatus(spawnSnakeTile2, 1);
    setStatus(spawnSnakeTile3, 1);
    snakeTiles.push_back(spawnSnakeTile3);
    snakeTiles.push_back(spawnSnakeTile2);
    snakeTiles.push_back(spawnSnakeTile1);
    renderSprite(spawnSnakeTile1, SNAKE_HEAD_RIGHT);
    renderSprite(spawnSnakeTile2, SNAKE_BODY_HORIZONTAL);
    renderSprite(spawnSnakeTile3, SNAKE_TAIL_LEFT);

    generateFood();
    updateScore();
}

void Snake::update()
{
    if (!gameOver) {
        delay(1.5 * (120 - Snake::snakeTiles.size()) + 200);
        moveSnake();
    }
}

void Snake::onGameClosed() 
{
    updateHighscore();
}

void Snake::keyPressed(int key) 
{
    if (key == 0 && Snake::lastMovedDirection != 2) {
        direction = 0;
    } else if (key == 1 && Snake::lastMovedDirection != 3) {
        direction = 1;
    } else if (key == 2 && Snake::lastMovedDirection != 0) {
        direction = 2;
    } else if (key == 3 && Snake::lastMovedDirection != 1) {
        direction = 3;
    }
}

void Snake::keyReleased(int key) 
{
    
}

void Snake::moveSnake() 
{
    Vector2D newSnakeTilePosition = snakeTiles[snakeTiles.size() - 1];

    switch (direction) {
        case 0: newSnakeTilePosition.addX(1); lastMovedDirection = 0; break;
        case 1: newSnakeTilePosition.addY(-1); lastMovedDirection = 1; break;
        case 2: newSnakeTilePosition.addX(-1); lastMovedDirection = 2; break;
        case 3: newSnakeTilePosition.addY(1); lastMovedDirection = 3; break;
    }

    Vector2D frontTilePosition = snakeTiles.front();
    int newSnakeTilePositionStatus = tiles[newSnakeTilePosition.getIntY()][newSnakeTilePosition.getIntX()];

    if (!(newSnakeTilePosition.getIntX() < gridX && newSnakeTilePosition.getIntX() >= 0 && newSnakeTilePosition.getIntY() < gridY && newSnakeTilePosition.getIntY() >= 0)) {
        playerGameOver();
        return;
    } else if (newSnakeTilePositionStatus != 2) {
        setStatus(frontTilePosition, 0);
    }

    if (tiles[newSnakeTilePosition.getIntY()][newSnakeTilePosition.getIntX()] == 1) {
        playerGameOver();
        return;
    }

    if (newSnakeTilePositionStatus == 2) {
        generateFood();
        pushSnakeTile(newSnakeTilePosition);
        updateScore();
    } else {
        pullSnakeTail();
        pushSnakeTile(newSnakeTilePosition);
    }
}

void Snake::pushSnakeTile(Vector2D newSnakeTileVector) 
{
    Vector2D secondVector = snakeTiles[snakeTiles.size() - 1];
    Vector2D thirdVector = snakeTiles[snakeTiles.size() - 2];
    Vector2D offsetFirstSecond = secondVector.copy().subtract(newSnakeTileVector);
    Vector2D offsetSecondThird = thirdVector.subtract(secondVector);

    if (offsetFirstSecond.getX() > 0) {
        renderSprite(newSnakeTileVector, SNAKE_HEAD_LEFT);
        if (offsetSecondThird.getX() > 0) {
            renderSprite(secondVector, SNAKE_BODY_HORIZONTAL);
        } else if (offsetSecondThird.getY() > 0) {
            renderSprite(secondVector, SNAKE_CORNER_TOP_RIGHT);
        } else if (offsetSecondThird.getY() < 0) {
            renderSprite(secondVector, SNAKE_CORNER_BOTTOM_RIGHT);
        }
    } else if (offsetFirstSecond.getX() < 0) {
        renderSprite(newSnakeTileVector, SNAKE_HEAD_RIGHT);
        if (offsetSecondThird.getX() < 0) {
            renderSprite(secondVector, SNAKE_BODY_HORIZONTAL);
        } else if (offsetSecondThird.getY() > 0) {
            renderSprite(secondVector, SNAKE_CORNER_TOP_LEFT);
        } else if (offsetSecondThird.getY() < 0) {
            renderSprite(secondVector, SNAKE_CORNER_BOTTOM_LEFT);
        }
    } else if (offsetFirstSecond.getY() > 0) {
        renderSprite(newSnakeTileVector, SNAKE_HEAD_UP);
        if (offsetSecondThird.getY() > 0) {
            renderSprite(secondVector, SNAKE_BODY_VERTICAL);
        } else if (offsetSecondThird.getX() > 0) {
            renderSprite(secondVector, SNAKE_CORNER_BOTTOM_LEFT);
        } else if (offsetSecondThird.getX() < 0) {
            renderSprite(secondVector, SNAKE_CORNER_BOTTOM_RIGHT);
        }
    } else if (offsetFirstSecond.getY() < 0) {
        renderSprite(newSnakeTileVector, SNAKE_HEAD_DOWN);
        if (offsetSecondThird.getY() < 0) {
            renderSprite(secondVector, SNAKE_BODY_VERTICAL);
        } else if (offsetSecondThird.getX() > 0) {
            renderSprite(secondVector, SNAKE_CORNER_TOP_LEFT);
        } else if (offsetSecondThird.getX() < 0) {
            renderSprite(secondVector, SNAKE_CORNER_TOP_RIGHT);
        }
    }

    setStatus(newSnakeTileVector, 1);
    snakeTiles.push_back(newSnakeTileVector);
}

void Snake::pullSnakeTail() 
{
    Vector2D newTailPosition = snakeTiles[1];
    Vector2D afterNewTailPosition = snakeTiles[2];
    
    Vector2D offset = newTailPosition.copy().subtract(afterNewTailPosition);

    if (offset.getX() > 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_RIGHT);
    } else if (offset.getX() < 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_LEFT);
    } else if (offset.getY() > 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_DOWN);
    } else if (offset.getY() < 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_UP);
    }

    resetTileColor(snakeTiles[0]);
    snakeTiles.erase(snakeTiles.begin());
}

void Snake::generateFood()
{
    std::vector<Vector2D> freeTiles;

    for (int row = 0; row < gridY; row++) {
        for (int col = 0; col < gridX; col++) {
            if (tiles[row][col] == 0) {
                freeTiles.push_back(Vector2D(col, row));
            }
        }
    }

    if (!freeTiles.empty()) {
        int randomTileIndex = random(freeTiles.size());
        setFoodTile(freeTiles[randomTileIndex]);
    } else {
        playerGameOver();
    }
}

void Snake::setStatus(Vector2D tilePosition, int status) 
{
    tiles[tilePosition.getIntY()][tilePosition.getIntX()] = status;
}

void Snake::setFoodTile(Vector2D foodTilePosition) 
{
    renderSprite(foodTilePosition, APPLE);
    setStatus(foodTilePosition, 2);
}

void Snake::resetTileColor(Vector2D tilePosition) 
{
    DisplayManager::getDisplay().fillRect(tilePosition.getIntX() * tileSize + offsetX, tilePosition.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_BLACK);
}

void Snake::renderSprite(Vector2D tilePosition, Vector2D sprite) 
{
    snakeSpriteSheet.pushImage(sprite.getIntX(), sprite.getIntY(), 150, 120, snakeBitmap);
    snakeSpriteSheet.pushSprite(tilePosition.getIntX() * tileSize + offsetX, tilePosition.getIntY() * tileSize + offsetY);
}

void Snake::playerGameOver()
{
    updateHighscore();
    DisplayManager::getDisplay().setTextColor(0xD800);
    DisplayManager::getDisplay().fillRoundRect(40, 40, 300, 60, 10, 0x3366);
    DisplayManager::getDisplay().setTextSize(3);
    DisplayManager::getDisplay().drawString("Game Over", 45, 45);
    DisplayManager::getDisplay().setTextSize(2);
    gameOver = true;
}

void Snake::updateHighscore() 
{
    if (snakeTiles.size() - 3 > highscore) {
        EEPROM.write(EEPROM_HIGHSCORE_ADDR, snakeTiles.size() - 3);
        EEPROM.commit();
    }
}

void Snake::updateScore() 
{
    DisplayManager::getDisplay().fillRoundRect(410, 10, 65, 40, 10, 0x3366);
    int score = snakeTiles.size() - 3;
    String scoreString = String(score);

    if (score < 10) {
        scoreString = "00" + scoreString;
    } else if (score < 100) {
        scoreString = "0" + scoreString;
    }

    DisplayManager::getDisplay().setTextColor(0x6ECD);
    DisplayManager::getDisplay().drawString(scoreString, 408, 15);

    if (score > highscore) {
        DisplayManager::getDisplay().setTextColor(0xF480);
        DisplayManager::getDisplay().fillRoundRect(410, 270, 65, 40, 10, 0x3366);
        DisplayManager::getDisplay().drawString(scoreString, 408, 275);
    }
}