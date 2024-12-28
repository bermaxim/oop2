#include "Game.h"
#include "GameState.h"  
#include "BoardRenderer.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>

Game::Game()
    : board(10, 10), shipManager({1, 2, 3, 4}), abilityManager(), playerTurn(true), boardRenderer(board) {
    shipManager.setAbilityManager(&abilityManager); 
    try {
        Ship& ship1 = shipManager.getShip(0);
        board.placeShip(ship1, 0, 0, Ship::Horizontal, &shipManager);

        Ship& ship2 = shipManager.getShip(1);
        board.placeShip(ship2, 2, 2, Ship::Vertical, &shipManager);

        Ship& ship3 = shipManager.getShip(2);
        board.placeShip(ship3, 5, 5, Ship::Horizontal, &shipManager);

        Ship& ship4 = shipManager.getShip(3);
        board.placeShip(ship4, 7, 0, Ship::Vertical, &shipManager);
    } catch (const InvalidShipPlacementException& e) {
        std::cerr << "Ошибка при размещении корабля: " << e.what() << std::endl;
    }
}

void Game::start() {
    bool gameOver = false;
    while (!gameOver) {
        if (playerTurn) {
            std::cout << "Ход игрока:\n";
            playerMove();
        } else {
            std::cout << "Ход компьютера:\n";
            computerMove();
        }

        checkGameStatus(gameOver);

        playerTurn = !playerTurn;
    }
}

void Game::initializeGame() { 
    board = GameBoard(10, 10);
    shipManager = ShipManager({1, 2, 3, 4});
    abilityManager = AbilityManager();
    shipManager.setAbilityManager(&abilityManager);
    playerTurn = true;
 
    try {
        Ship& ship1 = shipManager.getShip(0);
        board.placeShip(ship1, 0, 0, Ship::Horizontal, &shipManager);

        Ship& ship2 = shipManager.getShip(1);
        board.placeShip(ship2, 2, 2, Ship::Vertical, &shipManager);

        Ship& ship3 = shipManager.getShip(2);
        board.placeShip(ship3, 5, 5, Ship::Horizontal, &shipManager);

        Ship& ship4 = shipManager.getShip(3);
        board.placeShip(ship4, 7, 0, Ship::Vertical, &shipManager);
    } catch (const InvalidShipPlacementException& e) {
        std::cerr << "Ошибка при размещении корабля: " << e.what() << std::endl;
    }
}

void Game::playerMove() {
    std::cout << "Выберите действие:\n";
    std::cout << "1. Применить способность\n";
    std::cout << "2. Выполнить атаку\n";
    std::cout << "3. Сохранить игру\n";
    std::cout << "4. Загрузить игру\n";
    std::cout << "Выбор: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            try {
                abilityManager.useAbility(board, shipManager);
            } catch (const NoAbilitiesException& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
            break;
        case 2: {
            size_t x, y;
            std::cout << "Введите координаты атаки (x y): ";
            std::cin >> x >> y;
            try {
                board.attack(x, y, shipManager);
                boardRenderer.render();
            } catch (const OutOfBoundsAttackException& e) {
                std::cerr << "Ошибка при атаке: " << e.what() << std::endl;
            }
            break;
        }
        case 3:
            saveGame();
            break;
        case 4:
            loadGame();
            break;
        default:
            std::cout << "Неверный выбор.\n";
            break;
    }
}

void Game::computerMove() { 
    size_t x = rand() % board.getWidth();
    size_t y = rand() % board.getHeight();
    std::cout << "Компьютер атакует координаты (" << x << ", " << y << ")\n";
    try {
        board.attack(x, y, shipManager);
        boardRenderer.render();
    } catch (const OutOfBoundsAttackException& e) {
        std::cerr << "Ошибка при атаке компьютера: " << e.what() << std::endl;
    }
}

void Game::checkGameStatus(bool& gameOver) {
    if (shipManager.allShipsDestroyed()) {
        std::cout << "Все ваши корабли уничтожены. Вы проиграли!\n";
        std::cout << "Начать новую игру? (y/n): ";
        char response;
        std::cin >> response;
        if (response == 'y' || response == 'Y') {
            initializeGame();
            gameOver = false;
        } else {
            std::cout << "Игра окончена.\n";
            gameOver = true;
        }
    }
 
}

void Game::saveGame() {
    std::cout << "Введите имя файла для сохранения: ";
    std::string filename;
    std::cin >> filename;

    GameState state(board, shipManager, abilityManager);
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Не удалось открыть файл для сохранения.\n";
        return;
    }

    outFile << state;
    std::cout << "Игра сохранена в файл " << filename << "\n";
}

void Game::loadGame() {
    std::cout << "Введите имя файла для загрузки: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Не удалось открыть файл для загрузки.\n";
        return;
    }

    GameState state;
    inFile >> state;
 
    board = state.getBoard();
    shipManager = ShipManager();  
    for (size_t i = 0; i < state.getShipManager().getShipCount(); ++i) {
        Ship ship = state.getShipManager().getShip(i);
        shipManager.addShip(ship);
    }
    abilityManager = state.getAbilityManager(); 

    std::cout << "Игра загружена из файла " << filename << "\n";
}