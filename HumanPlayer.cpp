//
// Created by mfbut on 3/9/2019.
//

#include <utility>
#include "HumanPlayer.h"
#include "ShipPlacement.h"
#include "Attack.h"

BattleShip::HumanPlayer::HumanPlayer(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : Player(
        gameAttributes, view) {}

std::unique_ptr<BattleShip::Move> BattleShip::HumanPlayer::getMove() {
    std::pair<int, int> c;
    c = view.getFiringCoordinate(*this);
    return std::make_unique<Attack>(*this, c.first, c.second);
    //pointer of attack to *this, c.first coordinate, and c.second
}

void BattleShip::HumanPlayer::placeShips() {
    //iterate over each element
    ShipPlacement sh;
    for (auto& ship : shipHealths) {
        view.updateShipPlacementView(*this);
        sh = view.getShipPlacement(*this, ship.first, ship.second);
        board.AddShip(ship.first, sh);
    }
    view.updateShipPlacementView(*this);
}



void BattleShip::HumanPlayer::initializeName() {
    setName(view.getPlayerName(id+1));
}


