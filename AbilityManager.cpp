#include "AbilityManager.h"
#include <iostream> 
#include <ctime>    

AbilityManager::AbilityManager() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::unique_ptr<IAbility>> allAbilities;
    allAbilities.push_back(std::make_unique<DoubleDamage>());
    allAbilities.push_back(std::make_unique<Scanner>());
    allAbilities.push_back(std::make_unique<RandomStrike>());

    for (int i = 0; i < 3; ++i) {
        int r = rand() % (int)allAbilities.size();
        abilities.push(std::move(allAbilities[r]));
        allAbilities.erase(allAbilities.begin() + r);
    }

    std::cout << "The initial queue of abilities has been created. Queue size:" << abilities.size() << std::endl; 
}

void AbilityManager::useAbility(GameBoard& board, ShipManager& manager) {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }
    std::unique_ptr<IAbility> ability = std::move(abilities.front());
    abilities.pop();
    ability->apply(board, manager);

    std::cout << "The ability is used. Remaining abilities in the queue:: " << abilities.size() << std::endl;
}

void AbilityManager::addRandomAbilityToQueue() {
    int r = rand() % 3;
    switch (r) {
        case 0:
            abilities.push(std::make_unique<DoubleDamage>());
            std::cout << "Добавлена способность: Удвоение урона." << std::endl; 
            break;
        case 1:
            abilities.push(std::make_unique<Scanner>());
            std::cout << "Добавлена способность: Сканер." << std::endl; 
            break;
        case 2:
            abilities.push(std::make_unique<RandomStrike>());
            std::cout << "Добавлена способность: Бомбардировка." << std::endl; 
            break;
    }

    std::cout << "Текущий размер очереди способностей: " << abilities.size() << std::endl;
}

bool AbilityManager::empty() const {
    return abilities.empty();
}

void AbilityManager::onEnemyShipDestroyed() {
    std::cout << "Вражеский корабль уничтожен. Добавляется случайная способность..." << std::endl; 
    addRandomAbilityToQueue();
}