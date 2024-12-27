#include "PlacementException.h"

InvalidShipPlacementException::InvalidShipPlacementException()
    : std::runtime_error("Incorrect ship placement (touching or crossing with another ship).") {}