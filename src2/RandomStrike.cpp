#include "RandomStrike.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include "Ship.h"
#include <iostream>
#include <cstdlib>

RandomStrike::RandomStrike() {}

void RandomStrike::apply(GameBoard& board, ShipManager& manager) {
    (void)board; 

    std::vector<size_t> aliveShips;
    for (size_t i = 0; i < manager.getShipCount(); ++i) {
        if (!manager.getShip(i).isDestroyed()) {
            aliveShips.push_back(i);
        }
    }

    if (aliveShips.empty()) {
        std::cout << "There are no ships to fire on.\n";
        return;
    }

    size_t shipIndex = aliveShips[rand() % aliveShips.size()];
    Ship& ship = manager.getShip(shipIndex);

    std::vector<size_t> viableSegments;
    for (size_t i = 0; i < ship.getLength(); ++i) {
        auto state = ship.getSegmentState(i);
        if (state == Ship::Whole || state == Ship::Damage) {
            viableSegments.push_back(i);
        }
    }

    if (viableSegments.empty()) {
        std::cout << "The selected ship has already been destroyed.\n";
        return;
    }

    size_t segIndex = viableSegments[rand() % viableSegments.size()];
    ship.hitSegment(segIndex);

    std::cout << "The shelling caused damage to the ship " << shipIndex << " in segment " << segIndex << ".\n";

    if (ship.isDestroyed()) {
        std::cout << "Ship.h " << shipIndex << " destroyed! The player gets a new random ability.\n";
        manager.awardRandomAbility();
    }
}