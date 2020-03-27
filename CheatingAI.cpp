//
// Created by mfbut on 3/11/2019.
//
#include <stdexcept>
#include "CheatingAI.h"
#include "Attack.h"

BattleShip::CheatingAI::CheatingAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : AiPlayer(
        gameAttributes, view) {}



std::unique_ptr<BattleShip::Move> BattleShip::CheatingAI::getMove() {
    std::unique_ptr<Attack> att;
    for(int i = 0; i < opponent->getBoard().getNumCols(); i++) {
        for (int j = 0; j < opponent->getBoard().getNumRows(); j++) {
            if ((opponent->getBoard().at(j, i).containsShip()) && !((opponent->getBoard().at(j, i).HasBeenFiredAt()))) {
                att = std::make_unique<Attack>(*this, j, i);
                return att;
            }
        }
    }
    /*std::pair<int, int> target = vec.front(); //how to keep track of the number of turns
    auto temp = target;
    vec.erase(temp);*/
    throw "That has already been fired at.";
}

