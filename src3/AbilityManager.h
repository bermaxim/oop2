#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include <deque>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "IAbility.h"
#include "AbilityException.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "RandomStrike.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include <iostream>

class AbilityManager {
public:
    AbilityManager();

    AbilityManager(const AbilityManager& other);

    AbilityManager& operator=(const AbilityManager& other);
    
    void useAbility(GameBoard& board, ShipManager& manager);
    void addRandomAbilityToQueue();
    bool empty() const;

    void onEnemyShipDestroyed();

    friend std::ostream& operator<<(std::ostream& os, const AbilityManager& manager);
    friend std::istream& operator>>(std::istream& is, AbilityManager& manager);

private:
    std::deque<std::unique_ptr<IAbility>> abilities; 
    void copyAbilities(const AbilityManager& other);
};

#endif