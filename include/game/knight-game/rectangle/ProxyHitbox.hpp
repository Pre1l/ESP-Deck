#ifndef PROXY_HITBOX_HPP
#define PROXY_HITBOX_HPP

#include "Hitbox.hpp"

class ProxyHitbox : public Hitbox
{
    private:
        float offsetX;

    public:
        ProxyHitbox(std::shared_ptr<Vector2D> position, float width, float height, float offsetX);
        std::shared_ptr<Vector2D> getPosition() override;
};

#endif // PROXYHITBOX_HPP