#ifndef SCANNER_H
#define SCANNER_H

#include "IAbility.h"

class Scanner : public IAbility {
public:
    Scanner();
    void apply(GameBoard& board, ShipManager& manager) override;
    int getType() const override { return 1; }
    std::unique_ptr<IAbility> clone() const override; 
};

#endif