#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "math/Vector2D.hpp"
#include "game/Game.hpp"

class Snake : public Game
{
    private:
        int direction;
        int gridX;
        int gridY;
        int offsetX;
        int offsetY;
        int tileSize;
        int lastMovedDirection;
        int tiles[10][12];
        bool gameOver;
        std::vector<Vector2D> snakeTiles;

    public:
        Snake();
        void update() override;
        void input(int key) override;

    private:
        void setTileSnake(Vector2D vector);
        void setTileFood(Vector2D vector);
        void resetTileColor(Vector2D vector);
        void moveSnake();
        void setStatus(Vector2D vector, int status);
        void generateFood();
        void playerGameOver();
        void updateScore();
};

#endif // SNAKE_HPP