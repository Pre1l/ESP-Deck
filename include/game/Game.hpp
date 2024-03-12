#ifndef GAME_HPP
#define GAME_HPP

class Game 
{
    public:
        virtual void update() = 0;
        virtual void input(int key) = 0;
};

#endif // GAME_HPP