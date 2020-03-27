//
// Created by mfbut on 3/10/2019.
//

#include "Board.h"


BattleShip::Board::Board(int numRows, int numCols, char blankChar)
        : boardState(numRows, std::vector<Cell>(numCols, {blankChar})), blankChar(blankChar), numRows(numRows), numCols(numCols) {
}

BattleShip::Board::Board(int numRows, int numCols) : Board(numRows, numCols, '*') {}


bool BattleShip::Board::canPlaceShipAt(const ShipPlacement &shipPlacement) const {
    if (inBounds(shipPlacement)) {
        if (spacesAreEmpty(shipPlacement)) {
            return true;
        }
    }
    return false;
}

void BattleShip::Board::setNumRows(int numRows)  {
    this->numRows = numRows;
}

void BattleShip::Board::setNumCols(int numCols) {
    this->numCols = numCols;
}

int BattleShip::Board::getNumRows() const {
    return boardState.size();
}

int BattleShip::Board::getNumCols() const {
    return boardState.front().size();
}

std::vector<std::string> BattleShip::Board::getHiddenVersion() const {
    std::string str;
    std::vector<std::string> hiddenBoard(numRows);
    for(int x = 0; x < numRows; x++) {
        for(int y = 0; y < numCols; y++) {
            str.push_back(at(x,y).getContentsIfHidden());
        }
        hiddenBoard.at(x) = str;
        str.clear();
    }
    return hiddenBoard;
}

std::vector<std::string> BattleShip::Board::getVisibleVersion() const {
    std::string str;
    std::vector<std::string> visibleBoard(numRows);
    for(int x = 0; x < numRows; x++) {
        for(int y = 0; y < numCols; y++) {
            str.push_back(at(x,y).getContentsIfVisible());
        }
        visibleBoard.at(x) = str;
        str.clear();
    }
    return visibleBoard;
}

void BattleShip::Board::AddShip(char shipChar, const ShipPlacement &shipPlacement) {
    if (shipPlacement.rowStart == shipPlacement.rowEnd) {
        for(int i = shipPlacement.colStart; i <= shipPlacement.colEnd; i++) {
            at(shipPlacement.rowStart, i).setContents(shipChar);
        }
    } else {
        for(int j = shipPlacement.rowStart; j <= shipPlacement.rowEnd; j++) {
            at(j, shipPlacement.colStart).setContents(shipChar);
        }
    }
}

bool BattleShip::Board::inBounds(int row, int col) const {
    if ((row < 0) || (row >= numRows) || (col < 0) || (col >= numCols)) {
        return false;
    }
    return true;
}

BattleShip::Cell &BattleShip::Board::at(int i, int j) {
    return boardState[i][j];
}

const BattleShip::Cell &BattleShip::Board::at(int i, int j) const {
    return boardState[i][j];
}

bool BattleShip::Board::inBounds(const ShipPlacement &shipPlacement) const {
    if (inBounds(shipPlacement.rowStart, shipPlacement.colStart) &&
        inBounds(shipPlacement.rowEnd, shipPlacement.colEnd)) {
        return true;
    }
    return false;
}

bool BattleShip::Board::between(int value, int low, int high) const {
    if ((value >= low) && (value <= high)) {
        return true;
    }
    return false;
}

bool BattleShip::Board::spacesAreEmpty(const ShipPlacement &shipPlacement) const {
    int count = 0;
    if (shipPlacement.rowStart == shipPlacement.rowEnd) { //horizontal check
        for (int i = shipPlacement.colStart; i <= shipPlacement.colEnd; i++) {
            if (at(shipPlacement.rowStart, i).getContents() == blankChar) {
                count++;
            }
        }
        if(count == (((shipPlacement.colEnd)-(shipPlacement.colStart)))+1) {
            return true;
        }
    } else if (shipPlacement.colStart == shipPlacement.colEnd) {
        for (int j = shipPlacement.rowStart; j <= shipPlacement.rowEnd; j++) { //vertical check
            if (at(j, shipPlacement.colStart).getContents() == blankChar) {
                count++;
            }
        }
        if(count == (((shipPlacement.rowEnd)-(shipPlacement.rowStart))+1)) {
            return true;
        }
    }
    return false;
}


