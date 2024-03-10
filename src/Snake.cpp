#include "Snake.hpp"
#include "DisplayManager.hpp"
#include <ctime>

int Snake::direction = 0;
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
      //uint16_t color = (row % 2 == 0) ? ((col % 2 == 0) ? TFT_BLUE : TFT_CYAN) : ((col % 2 == 0) ? TFT_CYAN : TFT_BLUE);
      DisplayManager::getDisplay().fillRect(col * tileSize + offsetX, row * tileSize + offsetY, tileSize, tileSize, TFT_BLACK); 
      DisplayManager::getDisplay().drawRect(col * tileSize + offsetX, row * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN); 
    }
  }

  snakeTiles.push_back(Vector2D(0,4));
  snakeTiles.push_back(Vector2D(1,4));
  snakeTiles.push_back(Vector2D(2,4));

  setStatus(snakeTiles[0], 1);
  setStatus(snakeTiles[1], 1);
  setStatus(snakeTiles[2], 1);

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
    case 0: newVector.addX(1); break;
    case 1: newVector.addY(-1); break;
    case 2: newVector.addX(-1); break;
    case 3: newVector.addY(1); break;
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
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % freeTiles.size();
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
  //DisplayManager::getDisplay().fillCircle(vector.getIntX() * tileSize + tileSize/2 + offsetX, vector.getIntY() * tileSize + tileSize/2 + offsetY, tileSize/2 - 1, TFT_YELLOW);
  DisplayManager::getDisplay().fillRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_RED);
  DisplayManager::getDisplay().drawRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN);
  setStatus(vector, 2);
}

void Snake::resetTileColor(Vector2D vector) 
{
  //uint16_t color = (vector.getIntY() % 2 == 0) ? ((vector.getIntX() % 2 == 0) ? TFT_BLUE : TFT_CYAN) : ((vector.getIntX() % 2 == 0) ? TFT_CYAN : TFT_BLUE);
  DisplayManager::getDisplay().fillRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_BLACK);
  DisplayManager::getDisplay().drawRect(vector.getIntX() * tileSize + offsetX, vector.getIntY() * tileSize + offsetY, tileSize, tileSize, TFT_DARKGREEN); 
}

void Snake::updateScore() 
{
  DisplayManager::getDisplay().fillRect(450, 20, 30, 16, TFT_DARKGREEN);
  DisplayManager::getDisplay().drawString(String(snakeTiles.size()), 450, 20);
}