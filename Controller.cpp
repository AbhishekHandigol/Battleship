//
// Created by mfbut on 3/9/2019.
//

#include <stdexcept>
#include <vector>
#include <sstream>
#include "PlayerConfiguration.h"
#include "Controller.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "StandardView.h"
#include "CheatingAI.h"
#include "RandomAI.h"
#include "HuntDestroyAI.h"

BattleShip::Controller::Controller() : view(std::make_unique<StandardView>()) {}

void BattleShip::Controller::setupGame(const std::string &GameConfigurationFile, int seed) {
    AiPlayer::seed_random_number_generator(seed);
    model.loadGameConfigurationFromFile(GameConfigurationFile);
    setupGame();

}

void BattleShip::Controller::setupGame(const std::string &GameConfigurationFile) {
    model.loadGameConfigurationFromFile(GameConfigurationFile);
    setupGame();
}
//after prompting for AI, make the Ai's board with the ships already there
void BattleShip::Controller::setupGame() { //necessary?, add a function to print the board
    PlayerConfiguration p = view->getPlayerConfiguration();
    if (p.numHumanPlayers == 2) {
        model.addPlayer<HumanPlayer>(*view);
        model.addPlayer<HumanPlayer>(*view);
    }
    else if (p.numHumanPlayers == 1){
        model.addPlayer<HumanPlayer>(*view);
        int i = view->getAiChoice();
        if (i == 1) {
            model.addPlayer<CheatingAI>(*view);
        }
        if (i == 2) {
            model.addPlayer<RandomAI>(*view);
        }
        if(i == 3) {
            model.addPlayer<HuntDestroyAI>(*view);
        }
    } else if (p.numHumanPlayers == 0) {
        int i = view->getAiChoice();
        if (i == 1) {
            model.addPlayer<CheatingAI>(*view);
        }
        if (i == 2) {
            model.addPlayer<RandomAI>(*view);
        }
        if(i == 3) {
            model.addPlayer<HuntDestroyAI>(*view);
        }

        int j = view->getAiChoice();
        if (j == 1) {
            model.addPlayer<CheatingAI>(*view); //print the board
        }
        if (j == 2) {
            model.addPlayer<RandomAI>(*view);
        }
        if(j == 3) {
            model.addPlayer<HuntDestroyAI>(*view);
        }
    }
    model.SetOpponents();

}

void BattleShip::Controller::playGame() {
    //view->showPlayersBoard(model.getAttackingPlayer());
    while (!model.isGameOver()) {
        std::unique_ptr<Move> move = nullptr;
        move = model.getNextMove();
        move->enact(model, *view);
        model.changeTurn();
        view->showPlayersBoard(model.getAttackingPlayer());
    }
    view->showWinner(model.getWinner());
}


