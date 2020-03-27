//
// Created by mfbut on 3/10/2019.
//

#include <stdexcept>
#include "Cell.h"



BattleShip::Cell::Cell(char contents, const char hiddenMarker, const char hitMarker,
                       const char missMarker) : contents(contents), firedAt(false), hiddenMarker(hiddenMarker),
                                                hitMarker(hitMarker), missMarker(missMarker) {}

BattleShip::Cell::Cell(char contents) : Cell(contents, '*', 'X', 'O') {}

char BattleShip::Cell::getContents() const {
    return contents;
}

void BattleShip::Cell::setContents(char contents) {
    this->contents = contents;
}

char BattleShip::Cell::getContentsIfHidden() const {
    if((firedAt) && (containsShip())) {
        return hitMarker;
    } else if(firedAt && !(containsShip())){
        return missMarker;
    }
    return hiddenMarker;
}

char BattleShip::Cell::getContentsIfVisible() const {
    return contents;
}

bool BattleShip::Cell::HasBeenFiredAt() const {
    return firedAt;
}

void BattleShip::Cell::setHasBeenFiredAt(bool hasBeenFiredAt) {
    this->firedAt = hasBeenFiredAt;
}

bool BattleShip::Cell::containsShip() const {
    if ((contents != '*') && (contents != missMarker)){
        return true;
    }
    else {
        return false;
    }
}



