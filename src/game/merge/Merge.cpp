#include "game/merge/Merge.hpp"

#include "display/DisplayManager.hpp"
#include "bitmap/FactoryBackgroundBitmap.hpp"
#include <vector>
#include "font/Fonts.hpp"

Merge::Merge() 
{
    gameOver = false;
    score = 0;

    TFT_eSPI& display = DisplayManager::getDisplay();
    display.pushImage(0, 0, 480, 320, factoryBackgroundBitmap);
    display.fillRoundRect(15, 15, 290, 305, 10, TFT_BLACK);

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
                delay(100);
                generateRandomTile();
            }
            break;
        default:
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
        playerGameOver();
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
        case 2: color = 0xF7E7; break;
        case 4: color = 0xF9C7; break;
        case 8: color = 0xF5A7; break;
        case 16: color = 0xF385; break;
        case 32: color = 0xF163; break;
        case 64: color = 0xEE41; break;
        case 128: color = 0xEB21; break;
        case 256: color = 0xE8FF; break;
        case 512: color = 0x98DF; break;
        case 1024: color = 0x7BDF; break;
        case 2048: color = 0x3FDF; break;
    }

    display.fillRoundRect(position.getIntX() * 70 + 25, position.getIntY() * 70 + 25, 60, 60, 5, color);

    if (value != 0) {
        display.setTextColor(TFT_BLACK);
        display.setTextSize(1);
        display.setFreeFont(FF21);
        display.drawString(String(value), position.getIntX() * 70 + 30, position.getIntY() * 70 + 30);
        DisplayManager::resetFont();
    }
}

void Merge::playerGameOver() 
{
    gameOver = true;
}