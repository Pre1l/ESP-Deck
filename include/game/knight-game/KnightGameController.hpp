#ifndef KNIGHT_GAME_SINGLETON_HPP
#define KNIGHT_GAME_SINGLETON_HPP

#include "game/Game.hpp"
#include <memory>
#include "KnightGame.hpp"

class KnightGameController : public Game
{
    private:
        static std::shared_ptr<KnightGame> instance;

        static void startInstance();
        static void terminateInstance();
        void toggleInstance();

    public:
        KnightGameController();
        virtual ~KnightGameController() override;

        void update(float deltaTime) override;
        void keyPressed(Core::Key key) override;
        void keyReleased(Core::Key key) override;

        static std::shared_ptr<KnightGame> getInstance();
};

#endif // KNIGHT_GAME_SINGLETON_HPP