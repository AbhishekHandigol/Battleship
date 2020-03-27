//
// Created by mfbut on 3/9/2019.
//
#include <utility>
#include "Utility.h"
#include "GameAttributes.h"

BattleShip::GameAttributes::GameAttributes() {}

BattleShip::GameAttributes::GameAttributes(int numRows, int numCols) : numRows(numRows), numCols(numCols) {
    this->numRows = numRows;
    this->numCols = numCols;
}

BattleShip::GameAttributes::GameAttributes(std::istream &in) {
    if(in) {
        verifiedRead(in, numRows);
        verifiedRead(in, numCols);
        int numShips = -1;
        verifiedRead(in, numShips);

        char shipChar;
        int shipSize;
        for (int i = 0; i < numShips; i++) {
            verifiedRead(in, shipChar);
            verifiedRead(in, shipSize);
            shipAttributes.insert(std::pair<char, int>(shipChar, shipSize));
        }
    }
}

int BattleShip::GameAttributes::getNumRows() const {
    return this->numRows;
}

void BattleShip::GameAttributes::setNumRows(int numRows) {
    this->numRows = numRows;
}

int BattleShip::GameAttributes::getNumCols() const {
    return this->numCols;
}

void BattleShip::GameAttributes::setNumCols(int numCols) {
    this->numCols = numCols;
}

int BattleShip::GameAttributes::getShipSize(const char shipChar) const {
    return shipAttributes.at(shipChar); //how to use the map with ship char at that index to get its pair
}

const std::map<char, int> &BattleShip::GameAttributes::getShipAttributes() const {
    return shipAttributes;
}

std::istream& BattleShip::operator>>(std::istream &in, BattleShip::GameAttributes &gameAttributes) {
    gameAttributes = GameAttributes(in);
    return in;
}

