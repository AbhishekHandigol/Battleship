//
// Created by mfbut on 3/9/2019.
//

#include <algorithm>
#include <vector>
#include <cctype>
#include "StandardView.h"
#include "Utility.h"

BattleShip::StandardView::StandardView(std::istream &in, std::ostream &out) : in(in), out(out) {}

BattleShip::StandardView::StandardView() : in(std::cin), out(std::cout){
};

BattleShip::PlayerConfiguration BattleShip::StandardView::getPlayerConfiguration() {
    out << "What type of game do you want to play?" << std::endl;
    out << "1. Human vs Human" << std::endl;
    out << "2. Human vs AI" << std::endl;
    out << "3. AI vs AI" << std::endl;
    out << "Your choice: " << std::endl;
    int choice;
    in >> choice;
    if (choice == 1) {
        return PlayerConfiguration(2, 0);
    }
    if (choice == 2) {
        return PlayerConfiguration(1, 1);
    }
    if (choice == 3) {
        return PlayerConfiguration(0, 2);
    }
    else throw "That is not an option";
}

std::string BattleShip::StandardView::getPlayerName(int i) {
    std::string name;
    out << "Player " << i << " please enter your name:" << std::endl;
    in >> name;
    return name;
}

ShipPlacement BattleShip::StandardView::getShipPlacement(const BattleShip::Player &player, char shipChar, int shipLen) {
    out << player.getName() << ", do you want to place " << shipChar << " horizontally or vertically?" << std::endl;
    out << "Enter h for horizontal or v for vertical" << std::endl;
    out << "Your choice: " << std::endl;
    char orientation;
    in >> orientation;
    if ((orientation != 'h') && (orientation != 'v')) {
        getShipPlacement(player, shipChar, shipLen);
    }
    out << player.getName() << ", enter the row and column you want to place " << shipChar << ", which is " << shipLen << " long, at with a space in between row and col:" << std::endl;
    int row, col;
    in >> row >> col;
    ShipPlacement shipPlacement;
    if (player.getBoard().inBounds(row, col)) {
        shipPlacement.rowStart = row;
        shipPlacement.colStart = col;
        if (orientation == 'h') {
            shipPlacement.rowEnd = row;
            shipPlacement.colEnd = (col + shipLen) - 1;
        } else if (orientation == 'v') {
            shipPlacement.rowEnd = row + (shipLen - 1);
            shipPlacement.colEnd = col;
        }
    }
    return shipPlacement;
}

void BattleShip::StandardView::updateShipPlacementView(const BattleShip::Player &player) {
    printBoardAsVisible(player.getBoard());
}

std::pair<int, int> BattleShip::StandardView::getFiringCoordinate(const BattleShip::Player &attacker) {
    out << attacker.getName() << ", where would you like to fire?" << std::endl;
    out << "Enter your attack coordinate in the form row col:" << std::endl;
    int row, col;
    in >> row >> col;
    return std::pair<int, int>(row, col);
}

void BattleShip::StandardView::showWinner(const BattleShip::Player &winner) {
    out << std::endl;
    out << winner.getName() << " won the game!" << std::endl;
}

void BattleShip::StandardView::showResultOfAttack(const BattleShip::Player &attacker,
                                                  const BattleShip::AttackResult &attackResult) {
    if(attackResult.hit == true) {
        showPlayersBoard(attacker);
        out << attacker.getName() << " hit " << attacker.getOpponent().getName() << "'s " << attackResult.shipChar << "!" << std::endl;
    } else {
        showPlayersBoard(attacker);
        out << "Missed." << std::endl;
    }
    if(attackResult.destroyed == true) {
        out << attacker.getName() << " destroyed " << attacker.getOpponent().getName() << "'s " << attackResult.shipChar << "!" << std::endl;
        out << std::endl;
    }
}

void BattleShip::StandardView::showPlayersBoard(const BattleShip::Player &player) {
    out << player.getName() << "'s Firing Board" << std::endl;
    printBoardAsObscured(player.getOpponent().getBoard());
    out << std::endl;

    out << player.getName() << "'s Placement Board" << std::endl;
    printBoardAsVisible(player.getBoard());
    out << std::endl;
}

void BattleShip::StandardView::showPlacementBoard(const BattleShip::Player &player) {
    printBoardAsObscured(player.getBoard());
    out << std::endl;
}

void BattleShip::StandardView::printBoard(const std::vector<std::string> &board) {
    out << " ";
    for(unsigned i = 0; i < board.size(); i++) {
        out << " " << i;
    }
    out << std::endl;
    //rows bigger, columns smaller
    for(unsigned i = 0; i < board.size(); i++) {
        out << i;
        for(unsigned j = 0; j < board.front().size(); j++) {
            out << " " << board.at(i).at(j);
        }
        out << std::endl;
    }
}

void BattleShip::StandardView::printBoardAsVisible(const BattleShip::Board &board) {
    printBoard(board.getVisibleVersion());
}

void BattleShip::StandardView::printBoardAsObscured(const BattleShip::Board &board) {
    printBoard(board.getHiddenVersion());
}

int BattleShip::StandardView::getAiChoice() {
    out << "What AI do you want?" << std::endl;
    out << "1. Cheating AI" << std::endl;
    out << "2. Random AI" << std::endl;
    out << "3. Hunt Destroy AI" << std::endl;
    out << "Your choice:" << std::endl;
    int choice;
    in >> choice;
    return choice;
}

void BattleShip::StandardView::clearInput() {
    std::string s;
    in >> s;
    for(unsigned i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c == '\n') {
            s.erase(c);
            break;
        }
        if (c != ' ') {
            s.push_back(c);
        }
    }
}
