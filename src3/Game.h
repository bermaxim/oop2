#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "ShipManager.h"
#include "AbilityManager.h"
#include "GameState.h"
#include "BoardRenderer.h"
#include <string>

class Game {
public:
    Game();
    void start(); 

private:
    GameBoard board;
    ShipManager shipManager;
    AbilityManager abilityManager;
    bool playerTurn;
    BoardRenderer boardRenderer;

    void initializeGame();
    void playerMove();
    void computerMove();
    void checkGameStatus(bool& gameOver);
    void saveGame();
    void loadGame();
};

#endif