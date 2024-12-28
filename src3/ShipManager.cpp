#include "ShipManager.h"
#include "AbilityManager.h"
#include <stdexcept>

ShipManager::ShipManager()
    : ShipManager({1, 2, 3, 4}) {} 

ShipManager::ShipManager(const std::vector<size_t>& shipSizes) {
    initializeShips(shipSizes);
}

void ShipManager::initializeShips(const std::vector<size_t>& shipSizes) {
    for (size_t size : shipSizes) {
        ships.emplace_back(Ship(size, Ship::Horizontal));
    }
}

Ship& ShipManager::getShip(size_t index) {
    if (index >= ships.size()) {
        throw std::out_of_range("Неверный индекс корабля");
    }
    return ships[index];
}

const Ship& ShipManager::getShip(size_t index) const { 
    if (index >= ships.size()) {
        throw std::out_of_range("Неверный индекс корабля");
    }
    return ships[index];
}

bool ShipManager::allShipsDestroyed() const {
    for (const auto& ship : ships) {
        if (!ship.isDestroyed()) {
            return false;
        }
    }
    return true;
}

void ShipManager::awardRandomAbility() {
    if (abilityManager) {
        abilityManager->addRandomAbilityToQueue();
    }
}

void ShipManager::addShip(const Ship& ship) { 
    ships.push_back(ship);
}