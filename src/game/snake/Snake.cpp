#include "game/snake/Snake.hpp"
#include "display/DisplayManager.hpp"
#include <ctime>
#include "bitmap/SnakeBitmap.hpp"
#include "bitmap/AppleBitmap.hpp"
#include "bitmap/GreenBrickBackgroundBitmap.hpp"
#include "bitmap/TrophyDarkGreenBitmap.hpp"
#include "font/Fonts.hpp"
#include <core/Core.hpp>
#include <iostream>

Snake::Snake(int gamemode)
{
    this->gamemode = gamemode;
    init(true);
}

Snake::~Snake()
{
    onGameClosed();
}

void Snake::init(bool doRenderBackground)
{
    currentDirection = direction::RIGHT;
    lastMovedDirection = direction::RIGHT;
    lastDelayTime = 0;
    gameOver = false;

    snakeTiles.clear();
    snakeSpriteSheet.createSprite(30, 30);
    snakeSpriteSheet.setSwapBytes(true);

    highscore = EepromManager::readInt8(snakeHighscoreAddresses[gamemode]);

    // Render background
    if (doRenderBackground)
        renderBackground();

    // Render UI elements
    renderUI();

    // Reset tiles to status 0
    resetTiles();

    // Spawn snake
    spawnSnake();

    // Generate first food
    generateFood();

    // Update score
    updateScore();
}

void Snake::renderBackground() 
{
    DisplayManager::getDisplay().pushImage(0, 0, 480, 320, greenBrickBackgroundBitmap);
}

void Snake::renderUI() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    // Make game area black
    display.fillRect(offsetX, offsetY, gridX * tileSize, gridY * tileSize, TFT_BLACK);

    // Score apple area
    display.fillRoundRect(375, 10, 100, 40, 10, 0x3366);
    display.pushImage(377, 15, 30, 30, appleBitmap);

    // Highscore area
    display.fillRoundRect(375, 270, 100, 40, 10, 0x3366);
    display.pushImage(375, 272, 35, 35, trophyDarkGreenBitmap);
    display.setTextColor(0xF480);
    display.fillRoundRect(410, 270, 65, 40, 10, 0x3366);

    String highscoreString = String(highscore);

    if (highscore < 10) {
        highscoreString = "00" + highscoreString;
    } else if (highscore < 100) {
        highscoreString = "0" + highscoreString;
    }

    display.drawString(highscoreString, 408, 275);
}

void Snake::resetTiles() 
{
    for (int row = 0; row < gridY; ++row) {
        for (int col = 0; col < gridX; ++col) {
            tiles[row][col] = status::EMPTY;
        }
    }
}

void Snake::spawnSnake() 
{
    // Set initial snake position and render
    // Random snake area to the left because snake always starts with direction right
    std::vector<Vector2D> randomSnakeTiles;

    for (int row = 0; row < gridY; row++) {
        for (int col = 3; col < gridX - 6; col++) {
            randomSnakeTiles.push_back(Vector2D(col, row));
        }
    }

    // Get a random spawn position index from area
    int randomTileIndex = random(randomSnakeTiles.size());

    // Define initial positions for snake tiles for easier spawning
    Vector2D spawnSnakeTile1 = randomSnakeTiles[randomTileIndex];
    Vector2D spawnSnakeTile2 = spawnSnakeTile1.copy().subtractX(1);
    Vector2D spawnSnakeTile3 = spawnSnakeTile2.copy().subtractX(1);

    // Set status of each snake tile
    setStatus(spawnSnakeTile1, status::SNAKE);
    setStatus(spawnSnakeTile2, status::SNAKE);
    setStatus(spawnSnakeTile3, status::SNAKE);

    // Add snake tiles to the snake vector
    snakeTiles.push_back(spawnSnakeTile3);
    snakeTiles.push_back(spawnSnakeTile2);
    snakeTiles.push_back(spawnSnakeTile1);

    // Render snake sprites at tile positions
    renderSprite(spawnSnakeTile1, SNAKE_HEAD_RIGHT);
    renderSprite(spawnSnakeTile2, SNAKE_BODY_HORIZONTAL);
    renderSprite(spawnSnakeTile3, SNAKE_TAIL_LEFT);
}

void Snake::update(float deltaTime)
{
    if (gameOver)
        return;

    int delayTime;

    // Calculate delay time based on gamemode and current state
    switch (gamemode) {
        case 0: delayTime = round(300 - deltaTime + lastDelayTime); break;
        case 1: delayTime = round(160 - deltaTime + lastDelayTime); break;
        case 2: delayTime = round(1.5 * (120 - Snake::snakeTiles.size()) + 200 - deltaTime + lastDelayTime); break;
    }

    lastDelayTime = delayTime;

    // Check for < 0 to prevent freezes if you would somehow reach this state
    if (delayTime >= 0)
        delay(delayTime);

    moveSnake();
}

void Snake::onGameClosed()
{
    updateHighscore();
}

void Snake::keyPressed(int key)
{
    // If game over restart game
    if (gameOver) {
        init(false);
        return;
    }

    // Handle key presses to change snake direction
    if (key == 0 && lastMovedDirection != direction::LEFT) {
        currentDirection = direction::RIGHT;
    } else if (key == 1 && lastMovedDirection != direction::DOWN) {
        currentDirection = direction::UP;
    } else if (key == 2 && lastMovedDirection != direction::RIGHT) {
        currentDirection = direction::LEFT;
    } else if (key == 3 && lastMovedDirection != direction::UP) {
        currentDirection = direction::DOWN;
    }
}

void Snake::keyReleased(int key)
{
    // Currently not used/needed
}

void Snake::moveSnake() 
{
    Vector2D newSnakeTilePosition = snakeTiles[snakeTiles.size() - 1];

    // Move in currentDirection by 1 and update lastMovedDirection
    switch (currentDirection) {
        case direction::RIGHT: newSnakeTilePosition.addX(1); lastMovedDirection = direction::RIGHT; break;
        case direction::UP: newSnakeTilePosition.addY(-1); lastMovedDirection = direction::UP; break;
        case direction::LEFT: newSnakeTilePosition.addX(-1); lastMovedDirection = direction::LEFT; break;
        case direction::DOWN: newSnakeTilePosition.addY(1); lastMovedDirection = direction::DOWN; break;
    }

    Vector2D frontTilePosition = snakeTiles.front();

    // Get status of new tile snake just moved onto
    status newSnakeTilePositionStatus = tiles[newSnakeTilePosition.getIntY()][newSnakeTilePosition.getIntX()];

    // Check if snake is outside of grid
    if (!(newSnakeTilePosition.getIntX() < gridX && newSnakeTilePosition.getIntX() >= 0 && newSnakeTilePosition.getIntY() < gridY && newSnakeTilePosition.getIntY() >= 0)) {
        playerGameOver();
        return;
    // Check if not apple to approve that snake doesnt get longer by 1
    // Then set status of tail snake tile neutral 
    // This makes it possible that the snake can make a tight maneuver where the tail just moves out of the way letting the snake pass
    } else if (newSnakeTilePositionStatus != status::FOOD) {
        setStatus(frontTilePosition, status::EMPTY);
    }

    // Check if the new tile is a snake tile
    if (tiles[newSnakeTilePosition.getIntY()][newSnakeTilePosition.getIntX()] == status::SNAKE) {
        playerGameOver();
        return;
    }

    // Depending on apple tile or not, pull the snake tail or grow by 1
    if (newSnakeTilePositionStatus == status::FOOD) {
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

    // Render snake segment based on snake rotation course
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

    // Set status of tile to snake
    setStatus(newSnakeTileVector, status::SNAKE);

    // Finally add the tile to the snake vector
    snakeTiles.push_back(newSnakeTileVector);
}

void Snake::pullSnakeTail()
{
    Vector2D newTailPosition = snakeTiles[1];
    Vector2D afterNewTailPosition = snakeTiles[2];
    Vector2D offset = newTailPosition.copy().subtract(afterNewTailPosition);

    // Render snake tail based on snake rotation course
    if (offset.getX() > 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_RIGHT);
    } else if (offset.getX() < 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_LEFT);
    } else if (offset.getY() > 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_DOWN);
    } else if (offset.getY() < 0) {
        renderSprite(newTailPosition, SNAKE_TAIL_UP);
    }

    // Reset color of the old tail tile
    resetTileColor(snakeTiles[0]);

    // Finally remove the tail from the snake vector
    snakeTiles.erase(snakeTiles.begin());
}

void Snake::generateFood()
{
    std::vector<Vector2D> freeTiles;

    // Find available empty tiles for placing food
    for (int row = 0; row < gridY; row++) {
        for (int col = 0; col < gridX; col++) {
            if (tiles[row][col] == status::EMPTY) {
                freeTiles.push_back(Vector2D(col, row));
            }
        }
    }

    // End game/Win, if no free tiles available, the player holds 100% of the playable area
    if (freeTiles.empty()) {
        playerGameOver();
        return;
    }

    // Place food on a randomly chosen free tile
    int randomTileIndex = random(freeTiles.size());
    setFoodTile(freeTiles[randomTileIndex]);
}

void Snake::setStatus(Vector2D tilePosition, status status)
{
    tiles[tilePosition.getIntY()][tilePosition.getIntX()] = status;
}

void Snake::setFoodTile(Vector2D foodTilePosition)
{
    renderSprite(foodTilePosition, APPLE);
    setStatus(foodTilePosition, status::FOOD);
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

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setTextColor(0xD800);
    display.setTextSize(2);
    display.setFreeFont(FF32);

    delay(500);
    // Destory snake starting from impact end
    for (int i = snakeTiles.size() - 1; i >= 0; i--) {
        resetTileColor(snakeTiles[i]);
        DisplayManager::getDisplay().fillCircle(snakeTiles[i].getIntX() * tileSize + offsetX + 15, snakeTiles[i].getIntY() * tileSize + offsetY + 15, 5, 0x6ECD);
        delay(60);
    }

    // Display the final game over screen
    delay(200);
    display.drawString("Game", 53, 70);
    delay(600);
    display.drawString("Over", 69, 145);
    DisplayManager::resetFont();
    gameOver = true;
}

void Snake::updateHighscore()
{
    // If highscore beaten, update
    if (snakeTiles.size() - 3 > highscore) {
        EepromManager::writeInt8(snakeHighscoreAddresses[gamemode], snakeTiles.size() - 3);
    }
}

void Snake::updateScore()
{
    TFT_eSPI& display = DisplayManager::getDisplay();

    // Erase old score display
    display.fillRoundRect(410, 10, 65, 40, 10, 0x3366);

    // Calculate score by subtracting starting length
    int score = snakeTiles.size() - 3;

    // Format score to 3 digits
    String scoreString = String(score);

    if (score < 10) {
        scoreString = "00" + scoreString;
    } else if (score < 100) {
        scoreString = "0" + scoreString;
    }

    // Update display of the score
    display.setTextColor(0x6ECD);
    display.drawString(scoreString, 408, 15);

    // If score beats highscore, update display of highscore in sync with score
    if (score > highscore) {
        display.setTextColor(0xF480);
        display.fillRoundRect(410, 270, 65, 40, 10, 0x3366);
        display.drawString(scoreString, 408, 275);
    }
}