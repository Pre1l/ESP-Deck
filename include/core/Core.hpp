#ifndef CORE_HPP
#define CORE_HPP

#include <memory>
#include "game/Game.hpp"

void inputLoop(void * parameter);
void setup();
void loop();
void setCurrentGame(std::unique_ptr<Game> game);

#endif // CORE_HPP