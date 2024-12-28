#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "GameBoard.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include <fstream>
#include <iostream>

class GameState {
public:
    GameState() = default;
    GameState(const GameBoard& board, const ShipManager& shipManager, const AbilityManager& abilityManager);

    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);

    const GameBoard& getBoard() const { return board; }
    const ShipManager& getShipManager() const { return shipManager; }
    const AbilityManager& getAbilityManager() const { return abilityManager; }

private:
    GameBoard board;
    ShipManager shipManager;
    AbilityManager abilityManager;
};

#endif