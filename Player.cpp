//
// Created by mfbut on 3/9/2019.
//

#include "Player.h"

int BattleShip::Player::num_instances = 0;

BattleShip::Player::Player(const int id, const std::string &name, const std::map<char, int> &shipHealths,
                           BattleShip::View &view, const BattleShip::Board &board, BattleShip::Player *opponent) : id(
        id), name(name), shipHealths(shipHealths), view(view), board(board), opponent(opponent) {}


BattleShip::Player::Player(const GameAttributes& gameAttributes, View& view) :
    id(Player::num_instances),
    name("Name"),
    shipHealths(gameAttributes.getShipAttributes()),
    view(view),
    board(gameAttributes.getNumRows(), gameAttributes.getNumCols()),
    opponent(nullptr) {
    ++num_instances;
}




const std::string &BattleShip::Player::getName() const {
    return name;
}

void BattleShip::Player::setName(const std::string &name) {
    this->name = name;
}

const BattleShip::Board &BattleShip::Player::getBoard() const {
    return board;
}

BattleShip::Board &BattleShip::Player::getBoard() {
    return board;
}

const int BattleShip::Player::getId() const {
    return id;
}

/*bool BattleShip::Player::operator==(const BattleShip::Player &rhs) const {
    return false;
}

bool BattleShip::Player::operator!=(const BattleShip::Player &rhs) const {
    return false;
}*/

bool BattleShip::Player::allShipsSunk() const {
    if(shipHealths.size() == 0) {
        return true;
    }
    return false;
}
/*In attackResult, return true, true if the ship is hit and destroyed,
return true and false if the ship is only hit but not destroyed
and false and false if the ship is never hit by the attack.*/
BattleShip::AttackResult BattleShip::Player::fireAt(int row, int col) {
    char c = opponent->board.at(row, col).getContentsIfVisible();
    if (opponent->board.at(row, col).containsShip())  { //hit is true
        opponent->board.at(row, col).setContents('X');
        opponent->board.at(row, col).setHasBeenFiredAt(true);
        this->shipHealths.at(c) -= 1;
            if(this->shipHealths.at(c) == 0) { //hit and destroyed
                char a = c;
                this->shipHealths.erase(a);
                return BattleShip::AttackResult(true, true, c);
            } else {
                return BattleShip::AttackResult(true, false, c); //just hit
            }
    }
    opponent->board.at(row, col).setContents('O');
    opponent->board.at(row, col).setHasBeenFiredAt(true);
    return BattleShip::AttackResult(false, false, c);
}

BattleShip::Player &BattleShip::Player::getOpponent() {
    return *opponent;
}

const BattleShip::Player &BattleShip::Player::getOpponent() const {
    return *opponent;
}

void BattleShip::Player::setOpponent(BattleShip::Player &opponent) {
    this->opponent = &opponent;
}

bool BattleShip::Player::hit(char shipChar) { //check if the ship was destroyed
    bool destroyed = false;
    (shipHealths.at(shipChar))--;

    if (shipHealths.at(shipChar) == 0) {
        destroyed = true;
        shipHealths.erase(shipChar);
        return true;
    }
    return destroyed;
}


/*

BattleShip::Player::Player(const int id, const std::string &name, const std::map<char, int> &shipHealths,
                           BattleShip::View &view, const BattleShip::Board &board, BattleShip::Player *opponent) : id(
        id), name(name), shipHealths(shipHealths), view(view), board(board), opponent(opponent) {}
*/


