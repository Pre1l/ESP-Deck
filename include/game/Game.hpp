#ifndef GAME_HPP
#define GAME_HPP

class Game 
{
    public:
        virtual void update() = 0;
        virtual void keyPressed(int key) = 0;
        virtual void keyReleased(int key) = 0;
        virtual void onGameClosed() = 0;
};

#endif // GAME_HPP