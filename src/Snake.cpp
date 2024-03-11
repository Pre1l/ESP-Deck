#include "Snake.hpp"
#include "DisplayManager.hpp"
#include <ctime>

int Snake::direction = 0;
int Snake::lastMovedDirection = 0;
int Snake::gridX = 12;
int Snake::gridY = 10;
int Snake::tileSize = 30;
int Snake::offsetX = 10;
int Snake::offsetY = 10;
bool Snake::gameOver = false;
std::vector<Vector2D> Snake::snakeTiles;
int Snake::tiles[10][12];

void Snake::initialize() 
{
  DisplayManager::getDisplay().fillScreen(TFT_DARKGREEN);
  DisplayManager::getDisplay().setTextColor(TFT_GREEN);
  DisplayManager::getDisplay().setTextSize(2);
  DisplayManager::getDisplay().drawString("Score:", 380, 20);

  for (int row = 0; row < gridY; row++) {
    for (int col = 0; col < gridX; col++) {
      tiles[row][col] = 0;
      DisplayManager::getDisplay().fillRect(col * tileSize + offsetX, row * tileSize + offsetY, tileSize, tileSize, TFT_BLACK); 
      DisplayManager::getDisplay().drawRect(col * tileSize + offsetX, row * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN); 
    }
  }

  std::vector<Vector2D> randomSnakeTiles;

  for (int row = 0; row < gridY; row++) {
    for (int col = 0; col < gridX - 3; col++) {
        randomSnakeTiles.push_back(Vector2D(col, row));
    }
  }

  int randomIndex = random(randomSnakeTiles.size());

  snakeTiles.push_back(randomSnakeTiles[randomIndex]);
  setTileSnake(snakeTiles[0]);

  generateFood();
  updateScore();
}

void Snake::update()
{
  moveSnake();
}

void Snake::moveSnake() 
{
  Vector2D newVector = snakeTiles[snakeTiles.size() - 1];

  switch (direction) {
    case 0: newVector.addX(1); lastMovedDirection = 0; break;
    case 1: newVector.addY(-1); lastMovedDirection = 1; break;
    case 2: newVector.addX(-1); lastMovedDirection = 2; break;
    case 3: newVector.addY(1); lastMovedDirection = 3; break;
  }

  Vector2D frontVector = snakeTiles.front();
  int newVectorStatus = tiles[newVector.getIntY()][newVector.getIntX()];

  if (!(newVector.getIntX() < gridX && newVector.getIntX() >= 0 && newVector.getIntY() < gridY && newVector.getIntY() >= 0)) {
    playerGameOver();
    return;
  } else if (newVectorStatus != 2) {
    snakeTiles.erase(snakeTiles.begin());
    setStatus(frontVector, 0);
  }

  if (tiles[newVector.getIntY()][newVector.getIntX()] == 1) {
    playerGameOver();
    return;
  }
  
  if (newVectorStatus == 2) {
    generateFood();
  } else {
    resetTileColor(frontVector);
  }

  setTileSnake(newVector);
  snakeTiles.push_back(newVector);

  updateScore();
}

void Snake::playerGameOver()
{
  DisplayManager::getDisplay().setTextColor(TFT_RED);
  DisplayManager::getDisplay().setTextSize(2);
  DisplayManager::getDisplay().drawCentreString("Game Over", 190, 100, 4);
  gameOver = true;
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
    int randomIndex = random(freeTiles.size());
    setTileFood(freeTiles[randomIndex]);
  } else {
    playerGameOver();
  }
}

void Snake::setStatus(Vector2D vector, int status) 
{
  tiles[vector.getIntY()][vector.getIntX()] = status;
}

void Snake::setTileSnake(Vector2D vector) 
{
  DisplayManager::getDisplay().fillRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_GREEN);
  DisplayManager::getDisplay().drawRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN);
  setStatus(vector, 1);
}

void Snake::setTileFood(Vector2D vector) 
{
  DisplayManager::getDisplay().fillRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_RED);
  DisplayManager::getDisplay().drawRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN);
  setStatus(vector, 2);
}

void Snake::resetTileColor(Vector2D vector) 
{
  DisplayManager::getDisplay().fillRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_BLACK);
  DisplayManager::getDisplay().drawRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN); 
}

void Snake::updateScore() 
{
  DisplayManager::getDisplay().fillRect(450, 20, 30, 16, TFT_DARKGREEN);
  DisplayManager::getDisplay().drawString(String(snakeTiles.size()), 450, 20);
}