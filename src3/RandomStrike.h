#ifndef RANDOMSTRIKE_H
#define RANDOMSTRIKE_H

#include "IAbility.h"

class RandomStrike : public IAbility {
public:
    RandomStrike();
    void apply(GameBoard& board, ShipManager& manager) override;
    int getType() const override { return 2; }
    std::unique_ptr<IAbility> clone() const override;
};

#endif