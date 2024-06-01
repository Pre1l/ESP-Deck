#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include "Entity.hpp"
#include "game/knight-game/entity/CombatEntity.hpp"

class Knight : public CombatEntity
{
    public:
        Knight(std::shared_ptr<Vector2D> position);

    private:
        void setAnimation() override;
        void clearAfterImage(Vector2D& deltaVelocity) override;
        void pushAttackSprite() override;
        void pushMovementSprite() override;
        void clearCallbackAnimationAfterImage() override;
        void collisionWithCombatEntity(std::shared_ptr<CombatEntity> collisionCombatEntity, Rectangle::CollisionAxis axis) override;
};

#endif // KNIGHT_HPP