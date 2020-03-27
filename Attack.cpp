//
// Created by mfbut on 3/10/2019.
//

#include "Attack.h"


BattleShip::Attack::Attack(BattleShip::Player &attacker, const int row, const int col) : Move(attacker), row(row),
                                                                                          col(col) {}

bool BattleShip::Attack::isValid() const {
    return false;
}

const int BattleShip::Attack::getRow() const {
    return row;
}

const int BattleShip::Attack::getCol() const {
    return col;
}

void BattleShip::Attack::enact(BattleShip::Model &model, BattleShip::View &view) {
    if (!(moveMaker.getOpponent().getBoard().at(row, col).HasBeenFiredAt())) {
        AttackResult result = moveMaker.fireAt(row, col);
        view.showResultOfAttack(moveMaker, result);
    }
}
