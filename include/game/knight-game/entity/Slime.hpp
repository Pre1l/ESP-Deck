#ifndef SLIME_HPP
#define SLIME_HPP

#include "CombatEntity.hpp"

class Slime : public CombatEntity
{
    public:
        Slime(std::shared_ptr<Vector2D> position);
        void animationCallback() override;

    private:
        void setAnimation() override;
        void setAttackAnimation() override;
        void setDeathAnimation() override;
        void collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) override;
        void collisionWithTerrain(Rectangle::CollisionAxis axis) override;
};

#endif // SLIME_HPP