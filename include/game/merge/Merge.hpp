#ifndef MERGE_HPP
#define MERGE_HPP

#include "game/Game.hpp"
#include "math/Vector2D.hpp"

class Merge : public Game
{
    private:
        int tiles[4][4];
        int madeMoves;
        int score;
        bool gameOver;

    public:
        Merge();
        void update() override;
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void onGameClosed() override;

    private:
        void generateRandomTile();
        void playerGameOver();
        void moveInDirection(int direction);
        void setTile(int value, Vector2D position);
        void moveTile(Vector2D pattern, Vector2D tile, bool (&combinedTiles)[4][4], bool combined);
};

#endif // MERGE_HPP