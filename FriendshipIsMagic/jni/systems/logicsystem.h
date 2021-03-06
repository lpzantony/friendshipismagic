#pragma once
#include "system.h"
#include "../states/state.h"
#include "inputsystem.h"

class NetworkSystem;


enum Logic { 	moveRight, 		moveLeft, 	isJumping, 		fireOn, 	isFacingRight, 		isFacingLeft, 	canFire,
				coMoveRight, 	coMoveLeft,	coIsJumping,	coFireOn,	coIsFacingRight,	coIsFacingLeft,	coCanFire,
				changeDirection, coChangeDirection};

class LogicSystem: public System
{
     public:

         LogicSystem(World* world, State::Context& context, InputSystem* inputs, NetworkSystem* network);
         void update(sf::Time dt);

         bool getLogic(Logic l);
         void insertLogic(Logic l, bool);
         void setLogic(Logic l, bool);

     private:

        InputSystem* mInputs;
        NetworkSystem* mNetwork;

        std::map<Logic, bool> mLogics;
};
