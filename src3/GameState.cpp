#include "GameState.h"

GameState::GameState(const GameBoard& board, const ShipManager& shipManager, const AbilityManager& abilityManager)
    : board(board), shipManager(shipManager), abilityManager(abilityManager) {}

std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << state.board.getWidth() << ' ' << state.board.getHeight() << '\n';
    for (size_t y = 0; y < state.board.getHeight(); ++y) {
        for (size_t x = 0; x < state.board.getWidth(); ++x) {
            os << static_cast<int>(state.board.getCellStatus(x, y)) << ' ';
        }
        os << '\n';
    }

    os << state.shipManager.getShipCount() << '\n';
    for (size_t i = 0; i < state.shipManager.getShipCount(); ++i) {
        const Ship& ship = state.shipManager.getShip(i);
        os << ship.getLength() << ' ' << static_cast<int>(ship.getOrientation()) << ' ';
        for (size_t j = 0; j < ship.getLength(); ++j) {
            os << static_cast<int>(ship.getSegmentState(j)) << ' ';
        }
        os << '\n';
    }

    os << state.abilityManager;

    return os;
}

std::istream& operator>>(std::istream& is, GameState& state) {
    size_t width, height;
    is >> width >> height;
    state.board = GameBoard(width, height);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int cell;
            is >> cell;
            state.board.setCellStatus(x, y, static_cast<GameBoard::CellStatus>(cell));
        }
    }

    size_t shipCount;
    is >> shipCount;
    state.shipManager = ShipManager(); 
    for (size_t i = 0; i < shipCount; ++i) {
        size_t length;
        int orientationInt;
        is >> length >> orientationInt;
        Ship::Orientation orientation = static_cast<Ship::Orientation>(orientationInt);
        Ship ship(length, orientation);
        for (size_t j = 0; j < length; ++j) {
            int segmentStateInt;
            is >> segmentStateInt;
            Ship::SegmentState segmentState = static_cast<Ship::SegmentState>(segmentStateInt);
            ship.setSegmentState(j, segmentState);
        }
        state.shipManager.addShip(ship);
    }

    is >> state.abilityManager;

    return is;
}