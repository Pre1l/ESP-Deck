#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include "math/Vector2D.hpp"
#include "game/Game.hpp"
#include <TFT_eSPI.h>
#include "display/DisplayManager.hpp"
#include <eeprom/EepromManager.hpp>

class Snake : public Game
{
    private:
        enum class Status {
            EMPTY,
            FOOD,
            SNAKE
        };

        // Highscore addresses from all difficulties
        const int snakeHighscoreAddresses[3] = {
            EepromManager::EEPROM_SNAKE_CLASSIC_HIGHSCORE_ADDR_INT8,
            EepromManager::EEPROM_SNAKE_SPEED_HIGHSCORE_ADDR_INT8,
            EepromManager::EEPROM_SNAKE_RISING_HIGHSCORE_ADDR_INT8
        };

        static const int gridX = 12;
        static const int gridY = 10;
        static const int offsetX = 10;
        static const int offsetY = 10;
        static const int tileSize = 30;
        Status tiles[gridY][gridX];

        Core::Direction currentDirection;
        Core::Direction lastMovedDirection;
        int gamemode;
        int highscore;
        int lastDelayTime;

        bool gameOver;
        TFT_eSprite snakeSpriteSheet = TFT_eSprite(&DisplayManager::tft);
        std::vector<Vector2D> snakeTiles;

        // Sprite vector offsets to get to specific sprites on sprite sheet
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
        Snake(int gamemode);
        ~Snake() override;

        void update(float deltaTime) override;
        void keyPressed(Core::Key key) override;
        void keyReleased(Core::Key key) override;

    private:
        // Init
        void init(bool doRenderBackground);
        void renderBackground();
        void renderUI();
        void spawnSnake();
        void resetTiles();

        // General
        void moveSnake();
        void onGameClosed();
        void generateFood();
        void playerGameOver();
        void updateScore();
        void updateHighscore();

        // Tiles
        void pushSnakeTile(Vector2D newSnakeTileVector);
        void pullSnakeTail();
        void resetTileColor(Vector2D tilePosition);
        void renderSprite(Vector2D tilePosition, Vector2D sprite);
        void setFoodTile(Vector2D foodTilePosition);
        void setStatus(Vector2D tilePosition, Status Status);
};

#endif // SNAKE_HPP