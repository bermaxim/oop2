#include "AbilityManager.h"

AbilityManager::AbilityManager() { 
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<std::unique_ptr<IAbility>> allAbilities;
    allAbilities.push_back(std::make_unique<DoubleDamage>());
    allAbilities.push_back(std::make_unique<Scanner>());
    allAbilities.push_back(std::make_unique<RandomStrike>());

    for (int i = 0; i < 3 && !allAbilities.empty(); ++i) {
        int r = rand() % static_cast<int>(allAbilities.size());
        abilities.push_back(std::move(allAbilities[r]));
        allAbilities.erase(allAbilities.begin() + r);
    }

    std::cout << "Начальная очередь способностей создана. Размер очереди: " << abilities.size() << std::endl; 
}
 
void AbilityManager::copyAbilities(const AbilityManager& other) {
    abilities.clear();
    for (const auto& ability : other.abilities) {
        abilities.emplace_back(ability->clone());
    }
}

 
AbilityManager::AbilityManager(const AbilityManager& other) {
    copyAbilities(other);
}

AbilityManager& AbilityManager::operator=(const AbilityManager& other) {
    if (this != &other) {
        copyAbilities(other);
    }
    return *this;
}

void AbilityManager::useAbility(GameBoard& board, ShipManager& manager) {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }
    std::unique_ptr<IAbility> ability = std::move(abilities.front());
    abilities.pop_front();
    ability->apply(board, manager);

    std::cout << "Способность использована. Оставшиеся способности в очереди: " << abilities.size() << std::endl;
}

void AbilityManager::addRandomAbilityToQueue() {
    int r = rand() % 3;
    switch (r) {
        case 0:
            abilities.push_back(std::make_unique<DoubleDamage>());
            std::cout << "Добавлена способность: Удвоение урона." << std::endl; 
            break;
        case 1:
            abilities.push_back(std::make_unique<Scanner>());
            std::cout << "Добавлена способность: Сканер." << std::endl; 
            break;
        case 2:
            abilities.push_back(std::make_unique<RandomStrike>());
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

std::ostream& operator<<(std::ostream& os, const AbilityManager& manager) {
    os << manager.abilities.size() << '\n';
    for (const auto& ability : manager.abilities) {
        os << ability->getType() << ' ';
    }
    os << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, AbilityManager& manager) {
    size_t size;
    is >> size;
    manager.abilities.clear();
    for (size_t i = 0; i < size; ++i) {
        int type;
        is >> type;
        switch(type) {
            case 0:
                manager.abilities.push_back(std::make_unique<DoubleDamage>());
                break;
            case 1:
                manager.abilities.push_back(std::make_unique<Scanner>());
                break;
            case 2:
                manager.abilities.push_back(std::make_unique<RandomStrike>());
                break;
            default: 
                break;
        }
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return is;
}
