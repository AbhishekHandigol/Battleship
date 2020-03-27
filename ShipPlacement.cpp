//
// Created by mfbut on 3/10/2019.
//

#include <algorithm>
#include "ShipPlacement.h"

ShipPlacement::ShipPlacement() {}

ShipPlacement::ShipPlacement(int rowStart, int colStart, int rowEnd, int colEnd) : rowStart(rowStart),
                                                                                   colStart(colStart), rowEnd(rowEnd),
                                                                                   colEnd(colEnd) {}

void ShipPlacement::normalize() {
    if ((rowStart > rowEnd) || (colStart > colEnd)) {
        throw "Error in building the ship.";
    }
}



