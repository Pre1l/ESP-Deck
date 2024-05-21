#include "game/knight-game/rectangle/Hitbox.hpp"
#include <memory>

Hitbox::Hitbox(std::shared_ptr<Vector2D> position, float width, float height) 
: Rectangle(position, width, height)
{

}