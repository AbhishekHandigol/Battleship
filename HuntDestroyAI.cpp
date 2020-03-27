//
// Created by mfbut on 3/11/2019.
//

#include <algorithm>
#include "HuntDestroyAI.h"
#include "Attack.h"
#include "Utility.h"

BattleShip::HuntDestroyAI::HuntDestroyAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view)
        : RandomAI(gameAttributes, view) {}

/*Make sure the locations are in bounds
        Make sure that you haven't fired there yet and aren't planning to fire there in the future
        Make sure to remove that location from the RandomAi's firing locations so as not to have the random AI accidentally shoot the same spot twice.
        */
std::unique_ptr<BattleShip::Move> BattleShip::HuntDestroyAI::getMove() {
    std::unique_ptr<Attack> att;//I wanted to check if this location is in bounds but i'm not sure how to access the pair so i used c instead
    std::pair<int, int> c = priorityFiringQueue.front(); //what do i initialize c to?
    if(!priorityFiringQueue.empty())  {
        firingLocations.erase(priorityFiringQueue.begin());
        att = std::make_unique<Attack>(*this, (c).first, (c).second);
    } else {
        Attack* temp = dynamic_cast<Attack*>(RandomAI::getMove().release()); //sets the pointer to null, so the temporary variable can be deleted (needs to keep track of last hit)
        att.reset(temp);
    }
    std::pair<int, int> coord(att->getRow(), att->getCol()); //get the coordinates of the latest attack (done by random AI)
    if (opponent->getBoard().at(c.first, c.second).containsShip()) { //does the firing coordingate contain the last ship?
        auto surroundings = getSurroundingLocations(coord);
        for(const auto& i : surroundings) {
            if((std::find(firingLocations.begin(), firingLocations.end(), i) != firingLocations.end())) {
                firingLocations.push_back(i);
                firingLocations.erase((std::find(firingLocations.begin(), firingLocations.end(), i)));
                //firingLocations.erase(firingLocations.front());
            }
        }
    }
    return att;
}

std::vector<std::pair<int, int>>
BattleShip::HuntDestroyAI::getSurroundingLocations(const std::pair<int, int> &center) const {
    //left, up, right, down
    std::vector<std::pair<int, int>> surroundings;
    if(this->opponent->getBoard().inBounds(center.first, (center.second)-1)) {
        surroundings.push_back(std::pair<int, int>((center.first), (center.second)-1));
    }
    if(this->opponent->getBoard().inBounds((center.first)-1, center.second)) {
        surroundings.push_back(std::pair<int, int>((center.first)-1, (center.second)));
    }
    if(this->opponent->getBoard().inBounds(center.first, (center.second)+1)) {
        surroundings.push_back(std::pair<int, int>((center.first), (center.second)+1));
    }
    if(this->opponent->getBoard().inBounds((center.first)+1, center.second)) {
        surroundings.push_back(std::pair<int, int>((center.first)+1, (center.second)));
    }
    return surroundings;
}


