//
// Created by mfbut on 3/11/2019.
//

#include "RandomAI.h"
#include "Attack.h"
#include "Utility.h"

BattleShip::RandomAI::RandomAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : AiPlayer(
        gameAttributes, view) {
    for(int i = 0; i < board.getNumRows(); i++) {
        for(int j = 0; j < board.getNumCols(); j++) {
            std::pair<int, int> c (i, j);
            firingLocations.insert(firingLocations.begin(), c);
        }
    }
}

std::unique_ptr<BattleShip::Move> BattleShip::RandomAI::getMove() {
    auto target = chooseRandom(firingLocations, randomNumberGenerator);
    auto temp = target;
    firingLocations.erase(temp);
    return std::make_unique<Attack>(*this, (*target).first, (*target).second);
}
