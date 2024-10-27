#include "Inventory.h"
#include <iostream>

void Inventory::addItem(const Loot& item) {
    items.push_back(item);
}

void Inventory::displayItems() const {
    std::cout << "Player's Inventory: \n";
    for (const auto& item : items) {
        std::cout << "- " << item.getName() << "\n";
    }
}
