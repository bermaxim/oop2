#include "OutOfBoundsAttackException.h"

OutOfBoundsAttackException::OutOfBoundsAttackException()
    : std::runtime_error("The attack goes beyond the boundaries of the field.") {}