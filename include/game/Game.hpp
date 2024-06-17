#ifndef GAME_HPP
#define GAME_HPP

class Game 
{
    public:
        enum class GameType {
            OTHER,
            MENU
        };

    protected:
        int menuReturnIndex;
        GameType gameType = GameType::OTHER;

    public:
        virtual ~Game() {};

        virtual void update(float deltaTime) = 0;
        virtual void keyPressed(int key) = 0;
        virtual void keyReleased(int key) = 0;

        GameType getGameType() { return gameType; };
};

#endif // GAME_HPP