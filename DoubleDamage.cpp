#include "DoubleDamage.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include <iostream>

DoubleDamage::DoubleDamage() {}

void DoubleDamage::apply(GameBoard& board, ShipManager& manager) {
    (void)board;   
    (void)manager;
    std::cout << "ПThe 'Double Damage' ability has been applied. The next hit will cause additional damage.\n";
    board.enableDoubleDamageFlag(true);
}