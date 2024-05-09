#ifndef GAME_HPP
#define GAME_HPP

class Game 
{
    protected:
        int menuReturnIndex;

    public:
        virtual void update(float deltaTime) = 0;
        virtual void keyPressed(int key) = 0;
        virtual void keyReleased(int key) = 0;
        virtual void onGameClosed() = 0;
};

#endif // GAME_HPP