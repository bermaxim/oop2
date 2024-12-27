#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits> 
#include "ShipManager.h"
#include "GameBoard.h"
#include "BoardRenderer.h"
#include "AbilityManager.h"
#include "PlacementException.h"
#include "OutOfBoundsAttackException.h"
#include "AbilityException.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try {
        std::vector<size_t> shipSizes = {1, 2, 3, 4};
        ShipManager manager(shipSizes);
        GameBoard board(9, 9);
        AbilityManager abilityManager;

        manager.setAbilityManager(&abilityManager);

        abilityManager.useAbility(board, manager);

        Ship& ship1 = manager.getShip(1);
        board.placeShip(ship1, 5, 5, Ship::Vertical, &manager);

        Ship& ship2 = manager.getShip(2);
        board.placeShip(ship2, 0, 2, Ship::Horizontal, &manager);

        bool gameRunning = true;
        while (gameRunning) {
            BoardRenderer renderer(board);
            std::cout << "Игровое поле:" << std::endl;
            renderer.render();

            int x, y;
            std::cout << "Введите координаты для атаки (x y): ";
            std::cin >> x >> y;

            if (std::cin.fail() || x < 0 || x >= (int)board.getWidth() || y < 0 || y >= (int)board.getHeight()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Неверный ввод координат! Попробуйте снова.\n";
                continue; 
            }

            try {

                board.attack(x, y, manager);

                if (!abilityManager.empty()) {
                    abilityManager.useAbility(board, manager);
                }

                if (manager.allShipsDestroyed() != 0) {
                    std::cout << "Поздравляем, вы победили!" << std::endl;
                    gameRunning = false;
                }
            } catch (const OutOfBoundsAttackException& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
        }

    } catch (const NoAbilitiesException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const InvalidShipPlacementException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
