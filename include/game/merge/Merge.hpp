#ifndef MERGE_HPP
#define MERGE_HPP

#include "game/Game.hpp"
#include "math/Vector2D.hpp"
#include <vector>

class Merge : public Game
{
    private:
        int tiles[4][4];
        int madeMoves;
        int score;
        int highscore;
        bool gameOver;

    public:
        Merge();
        ~Merge() override;

        void update(float deltaTime) override;
        void keyPressed(Core::Key key) override;
        void keyReleased(Core::Key key) override;

    private:
        void onGameClosed();
        void generateRandomTile();
        void checkForGameOver();
        void playerGameOver();
        void updateHighscore();
        void updateScore();
        void init(bool renderBackground);
        void moveInDirection(Core::Direction direction);
        void setTile(int value, Vector2D position);
        void moveTile(Vector2D pattern, Vector2D tile, bool (&combinedTiles)[4][4], bool combined);
};

#endif // MERGE_HPP