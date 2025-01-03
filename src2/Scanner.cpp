#include "Scanner.h"
#include "GameBoard.h"
#include "ShipManager.h"
#include <iostream>
#include <cstdlib>

Scanner::Scanner() {}

void Scanner::apply(GameBoard& board, ShipManager& manager) {
    (void)manager;

    size_t w = board.getWidth();
    size_t h = board.getHeight();
    if (w < 2 || h < 2) {
        std::cout << "Not enough space to scan.\n";
        return;
    }

    size_t startX = rand() % (w - 1);
    size_t startY = rand() % (h - 1);

    bool foundShipSegment = false;
    for (size_t y = startY; y < startY + 2; ++y) {
        for (size_t x = startX; x < startX + 2; ++x) {
            if (board.getCellStatus(x, y) == GameBoard::ShipCell) {
                foundShipSegment = true;
                break;
            }
        }
        if (foundShipSegment) break;
    }

    std::cout << "Site scanning (" << startX << "," << startY << ") - ("
              << startX+1 << "," << startY+1 << "): "
              << (foundShipSegment ? "Ship segments have been detected." : "Empty.") << "\n";
}