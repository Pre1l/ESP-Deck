#include "game/GameFactory.hpp"

std::unique_ptr<Game> GameFactory::createUniqueKnightGame() 
{
    return std::unique_ptr<Game>(KnightGame::getInstance().get());
}