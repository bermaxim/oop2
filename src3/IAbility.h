#ifndef IABILITY_H
#define IABILITY_H

#include <memory>

class GameBoard;
class ShipManager;

class IAbility {
public:
    virtual ~IAbility() = default;
    virtual void apply(GameBoard& board, ShipManager& manager) = 0;
    virtual int getType() const = 0;
    virtual std::unique_ptr<IAbility> clone() const = 0; 
};

#endif