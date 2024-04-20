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
        int highscore;
        std::vector<Vector2D> snakeTiles;

        const Vector2D SNAKE_HEAD_UP = Vector2D(-90, 0);
        const Vector2D SNAKE_HEAD_LEFT = Vector2D(-90, -30);
        const Vector2D SNAKE_HEAD_RIGHT = Vector2D(-120, 0);
        const Vector2D SNAKE_HEAD_DOWN = Vector2D(-120, -30);

        const Vector2D SNAKE_TAIL_UP = Vector2D(-120, -90);
        const Vector2D SNAKE_TAIL_LEFT = Vector2D(-120, -60);
        const Vector2D SNAKE_TAIL_RIGHT = Vector2D(-90, -90);
        const Vector2D SNAKE_TAIL_DOWN = Vector2D(-90, -60);

        const Vector2D SNAKE_CORNER_TOP_LEFT = Vector2D(0, 0);
        const Vector2D SNAKE_CORNER_TOP_RIGHT = Vector2D(-60, 0);
        const Vector2D SNAKE_CORNER_BOTTOM_LEFT = Vector2D(0, -30);
        const Vector2D SNAKE_CORNER_BOTTOM_RIGHT = Vector2D(-60, -60);

        const Vector2D SNAKE_BODY_HORIZONTAL = Vector2D(-30, 0);
        const Vector2D SNAKE_BODY_VERTICAL = Vector2D(-60, -30);

        const Vector2D APPLE = Vector2D(0, -90);

    public:
        Snake();
        void update() override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;

    private:
        void pushSnakeTile(Vector2D newSnakeTileVector);
        void setFoodTile(Vector2D foodTilePosition);
        void resetTileColor(Vector2D tilePosition);
        void moveSnake();
        void setStatus(Vector2D tilePosition, int status);
        void generateFood();
        void playerGameOver();
        void updateScore();
        void renderSprite(Vector2D tilePosition, Vector2D sprite);
        void pullSnakeTail();
};

#endif // SNAKE_HPP