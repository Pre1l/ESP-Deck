#include "game/knight-game/KnightGameController.hpp"

#include <memory>
#include <iostream>

std::shared_ptr<KnightGame> KnightGameController::instance = nullptr;

KnightGameController::KnightGameController() 
{
    toggleInstance();
}

KnightGameController::~KnightGameController() 
{
    toggleInstance();
}

void KnightGameController::toggleInstance() 
{
    if (instance)
        terminateInstance();
    else   
        startInstance();
}

std::shared_ptr<KnightGame> KnightGameController::getInstance() 
{
    return instance;    
}

void KnightGameController::startInstance() 
{   
    if (!instance)
        instance = std::make_shared<KnightGame>();
}

void KnightGameController::terminateInstance() 
{
    instance.reset();
}

void KnightGameController::update(float deltaTime) 
{
    if (instance)
        instance->update(deltaTime);
}

void KnightGameController::keyPressed(Core::Key key) 
{
    if (instance)
        instance->keyPressed(key);
}
void KnightGameController::keyReleased(Core::Key key) 
{
    if (instance)
        instance->keyReleased(key);
}