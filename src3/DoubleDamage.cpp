#include "DoubleDamage.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include <iostream>

DoubleDamage::DoubleDamage() {}

void DoubleDamage::apply(GameBoard& board, ShipManager& manager) {
    (void)manager;
    board.enableDoubleDamageFlag(true);
    std::cout << "Применена способность 'Двойной урон'. Следующая атака нанесет дополнительный урон.\n";
}

std::unique_ptr<IAbility> DoubleDamage::clone() const { 
    return std::make_unique<DoubleDamage>(*this);
}