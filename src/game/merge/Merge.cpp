#include "game/merge/Merge.hpp"

#include "display/DisplayManager.hpp"
#include "bitmap/FactoryBackgroundBitmap.hpp"
#include <vector>
#include "font/Fonts.hpp"
#include "bitmap/WorkerTrophyBitmap.hpp"
#include "bitmap/WorkerBitmap.hpp"
#include <core/Core.hpp>
#include <eeprom/EepromManager.hpp>

Merge::Merge() 
{
    gameOver = false;
    score = 0;
    highscore = EepromManager::readInt16(EepromManager::EEPROM_MERGE_HIGHSCORE_ADDR_INT16);

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.pushImage(0, 0, 480, 320, factoryBackgroundBitmap);
    display.fillRoundRect(15, 15, 290, 290, 10, 0x1082);

    display.fillRoundRect(320, 15, 145, 60, 5, 0x1082);
    display.pushImage(335, 30, 30, 30, workerBitmap);
    updateScore();

    display.fillRoundRect(320, 250, 145, 60, 5, 0x1082);
    display.pushImage(320, 255, 50, 50, workerTrophyBitmap);

    display.setTextColor(0xFF73);
    display.setTextSize(1);
    display.fillRoundRect(370, 250, 95, 60, 5, 0x1082);
    display.drawString("$" + String(highscore), 370, 273);
    DisplayManager::resetFont();

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            tiles[row][col] = 0;
            display.fillRoundRect(col * 70 + 25, row * 70 + 25, 60, 60, 5, TFT_DARKGREY);
        }
    }

    generateRandomTile();
    generateRandomTile();
}

void Merge::update() 
{
    
}

void Merge::onGameClosed() 
{
    updateHighscore();
}

void Merge::keyPressed(int key) 
{
    switch (key) {
        case 0: 
        case 1: 
        case 2: 
        case 3:
            if (!gameOver) {
                moveInDirection(key);
                // delay(100);
                generateRandomTile();
                checkForGameOver();
            }
            break;
        default:
            // playerGameOver();
            break;
    }
}

void Merge::moveInDirection(int direction) 
{
    bool combinedTiles[4][4];

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            combinedTiles[row][col] = false;
        }
    }

    switch (direction) {
        case 0:
            for (int row = 0; row < 4; row++) {
                for (int col = 3; col >= 0; col--) {
                    if (tiles[row][col] != 0) {
                        moveTile(Vector2D(1, 0), Vector2D(col, row), combinedTiles, false);
                    }
                }
            }
            break;
        case 1:
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    if (tiles[row][col] != 0) {
                        moveTile(Vector2D(0, -1), Vector2D(col, row), combinedTiles, false);
                    }
                }
            }
            break;
        case 2:
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    if (tiles[row][col] != 0) {
                        moveTile(Vector2D(-1, 0), Vector2D(col, row), combinedTiles, false);
                    }
                }
            }
            break;
        case 3:
            for (int row = 4; row >= 0; row--) {
                for (int col = 0; col < 4; col++) {
                    if (tiles[row][col] != 0) {
                        moveTile(Vector2D(0, 1), Vector2D(col, row), combinedTiles, false);
                    }
                }
            }
            break;
    }
}

void Merge::moveTile(Vector2D pattern, Vector2D tilePosition, bool (&combinedTiles)[4][4], bool combined) 
{
    delay(10);
    if (tilePosition.getIntX() + pattern.getIntX() > 3 || tilePosition.getIntX() + pattern.getIntX() < 0 ||
        tilePosition.getIntY() + pattern.getIntY() > 3 || tilePosition.getIntY() + pattern.getIntY() < 0) {
        if (combined) {
            combinedTiles[tilePosition.getIntY()][tilePosition.getIntX()] = true;
        }
        return;
    }

    int tileStatus = tiles[tilePosition.getIntY()][tilePosition.getIntX()];
    Vector2D nextTilePosition = Vector2D(tilePosition.getIntX(), tilePosition.getIntY());
    nextTilePosition.add(pattern);
    int nextTileStatus = tiles[nextTilePosition.getIntY()][nextTilePosition.getIntX()];

    if (nextTileStatus == 0) {
        setTile(0, tilePosition);
        setTile(tileStatus, nextTilePosition);
        moveTile(pattern, nextTilePosition, combinedTiles, combined);
    } else if (tileStatus == nextTileStatus && !combined && !combinedTiles[nextTilePosition.getIntY()][nextTilePosition.getIntX()]) {
        setTile(0, tilePosition);
        score += tileStatus*2;
        updateScore();
        setTile(tileStatus*2, nextTilePosition);
        moveTile(pattern, nextTilePosition, combinedTiles, true);
    } else {
        if (combined) {
            combinedTiles[tilePosition.getIntY()][tilePosition.getIntX()] = true;
        }
    }
}

void Merge::keyReleased(int key) 
{
    
}

void Merge::updateHighscore()
{
    if (score > highscore) {
        EepromManager::writeInt16(EepromManager::EEPROM_MERGE_HIGHSCORE_ADDR_INT16, score);
    }
}

void Merge::updateScore() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setTextSize(1);
    display.fillRoundRect(370, 15, 95, 60, 5, 0x1082);
    String scoreString = "$" + String(score);

    display.setTextColor(TFT_WHITE);
    display.drawString(scoreString, 370, 38);

    if (score > highscore) {
        display.setTextColor(0xFF73);
        display.fillRoundRect(370, 250, 95, 60, 5, 0x1082);
        display.drawString(scoreString, 370, 273);
    }

    DisplayManager::resetFont();
}

void Merge::generateRandomTile() 
{
    std::vector<Vector2D> freeTiles;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (tiles[row][col] == 0) {
                freeTiles.push_back(Vector2D(col, row));
            }
        }
    }

    if (freeTiles.empty()) {
        return;
    }

    int randomTileIndex = random(freeTiles.size());
    setTile(2, freeTiles[randomTileIndex]);
}

void Merge::setTile(int value, Vector2D position) 
{
    tiles[position.getIntY()][position.getIntX()] = value;
    TFT_eSPI& display = DisplayManager::getDisplay();
    uint16_t color = TFT_DARKGREY;

    switch (value) {
        case 2: color = 0xFFFF; break;
        case 4: color = 0xE71C; break;
        case 8: color = 0xFAC0; break;
        case 16: color = 0xF7A5; break;
        case 32: color = 0x07E0; break;
        case 64: color = 0xF800; break;
        case 128: color = 0x0210; break;
        case 256: color = 0xFFE0; break;
        case 512: color = 0xEA85; break;
        case 1024: color = 0x4FD9; break;
        case 2048: color = 0x66D5; break;
    }

    display.fillRoundRect(position.getIntX() * 70 + 25, position.getIntY() * 70 + 25, 60, 60, 5, color);

    if (value == 0)
        return;

    display.setTextColor(0x3166);
    display.setTextSize(1);
    display.setFreeFont(FF21);
    display.drawString("$" + String(value), position.getIntX() * 70 + 30, position.getIntY() * 70 + 30);
    DisplayManager::resetFont();
}

void Merge::checkForGameOver() 
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (j != 3 && (tiles[i][j] == tiles[i][j + 1] || tiles[j][i] == tiles[j + 1][i]) || tiles[j][i] == 0) {
                return;
            }
        }
    }

    playerGameOver();
}

void Merge::playerGameOver() 
{
    TFT_eSPI& display = DisplayManager::getDisplay();
    display.setTextColor(TFT_RED);
    display.setTextSize(2);
    display.setFreeFont(FF32);

    delay(1000);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            display.fillRoundRect(col * 70 + 25, row * 70 + 25, 60, 60, 5, TFT_DARKGREY);
            delay(50);
        }
    }
    delay(500);
    for (int i = 0; i < 8; i++) {
        display.fillRect(i*35 + 30, 15, 15, 290, 0x2124);
        int randomDelay = random(250);
        delay(60 + randomDelay);
    }
    delay(200);
    display.drawString("Game", 23, 70);
    delay(600);
    display.drawString("Over", 39, 145);

    DisplayManager::resetFont();
    updateHighscore();
    gameOver = true;
}