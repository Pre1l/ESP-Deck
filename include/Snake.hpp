#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "Vector2D.hpp"

namespace Snake 
{
    extern int direction;
    extern int gridX;
    extern int gridY;
    extern int offsetX;
    extern int offsetY;
    extern bool gameOver;
    extern int tileSize;
    extern int tiles[10][12];
    extern std::vector<Vector2D> snakeTiles;

    void initialize();
    void update();
    void setTileSnake(Vector2D vector);
    void setTileFood(Vector2D vector);
    void resetTileColor(Vector2D vector);
    void moveSnake();
    void setStatus(Vector2D vector, int status);
    void generateFood();
    void playerGameOver();
    void updateScore();
}

#endif // SNAKE_HPP