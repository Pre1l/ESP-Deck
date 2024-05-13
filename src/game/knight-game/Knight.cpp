#include "game/knight-game/Knight.hpp"

Knight::Knight(Vector2D& position) 
: Entity(position, Vector2D(0, 0), Hitbox(position, 54, 64))
{
    
}