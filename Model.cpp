//
// Created by mfbut on 3/9/2019.
//

#include <fstream>
#include <algorithm>
#include "Model.h"

BattleShip::Model::Model() {
    playerTurn = 0;
}



BattleShip::Player &BattleShip::Model::getAttackingPlayer() {
    return *players.at(playerTurn);
}
//getAttackingPlayer().getMove()
const BattleShip::Player &BattleShip::Model::getAttackingPlayer() const {
    return *players.at(playerTurn);
}

BattleShip::Player &BattleShip::Model::getDefendingPlayer() {
    //changeTurn();
    return players.at(playerTurn)->getOpponent();
}

const BattleShip::Player &BattleShip::Model::getDefendingPlayer() const {
    //changeTurn();
    return players.at(playerTurn)->getOpponent();
}

bool BattleShip::Model::isGameOver() const {
    if(getAttackingPlayer().getOpponent().allShipsSunk()) {
        return true;
    }
    return false;
}

void BattleShip::Model::changeTurn() {
    if(playerTurn >= 1) {
        playerTurn = 0;
    } else if (playerTurn == 0) {
        playerTurn = 1;
    }
}

void BattleShip::Model::loadGameConfigurationFromFile(const std::string &gameConfigurationFile) {
    std::ifstream myFile(gameConfigurationFile);
    myFile >> gameAttributes;
}


std::unique_ptr<BattleShip::Move> BattleShip::Model::getNextMove() {
    std::unique_ptr<Move> move;
    move = getAttackingPlayer().getMove();
    return move;
}

BattleShip::Player &BattleShip::Model::getWinner() {
    changeTurn();
    return getAttackingPlayer();
}

void BattleShip::Model::SetOpponents() {
    players.front()->setOpponent(*players.back());
    players.back()->setOpponent(*players.front());
}

std::vector<std::unique_ptr<BattleShip::Player>> BattleShip::Model::getPlayers() {
    return std::vector<std::unique_ptr<BattleShip::Player>>();
}




