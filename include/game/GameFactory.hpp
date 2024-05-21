#ifndef GAME_FACTORY_HPP
#define GAME_FACTORY_HPP

#include <memory>
#include "Game.hpp"
#include "knight-game/KnightGame.hpp"

class GameFactory 
{
    public:
        static std::unique_ptr<Game> createUniqueKnightGame();
};

#endif // GAME_FACTORY_HPP