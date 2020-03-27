//
// Created by mfbut on 3/10/2019.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#include <string>
#include <vector>
#include "ShipPlacement.h"
#include "Cell.h"

namespace BattleShip {
class Board {
 public:


    Board(int numRows, int numCols);

    Board(int numRows, int numCols, const char blankChar);
    Board(int numRows, int numCols, const std::vector<std::vector<Cell>> &boardState, char blankChar);


    bool canPlaceShipAt(const ShipPlacement& shipPlacement) const;


  void setNumRows(int numRows);
  void setNumCols(int numCols);

  int getNumRows() const;
  int getNumCols() const;

  std::vector<std::string> getHiddenVersion() const;
  std::vector<std::string> getVisibleVersion() const;

  void AddShip(char shipChar, const ShipPlacement& shipPlacement);
  bool inBounds(int row, int col) const;

  Cell& at(int i, int j);
  const Cell& at(int i, int j) const;


 protected:
  bool inBounds(const ShipPlacement& shipPlacement) const;

  bool between(int value, int low, int high) const;
  bool spacesAreEmpty(const ShipPlacement& shipPlacement) const;

  //members
  std::vector<std::vector<Cell>> boardState;
  const char blankChar;
  int numRows;
  int numCols;

};
}

#endif //BATTLESHIP_BOARD_H
