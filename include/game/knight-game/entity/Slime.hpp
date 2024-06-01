#ifndef SLIME_HPP
#define SLIME_HPP

#include "CombatEntity.hpp"

class Slime : public CombatEntity
{
    public:
        Slime(std::shared_ptr<Vector2D> position);

    private:
        void setAnimation() override;
};

#endif // SLIME_HPP