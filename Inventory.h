#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include "Loot.h"

class Inventory {
public:
    void addItem(const Loot& item);
    void displayItems() const;

private:
    std::vector<Loot> items;  // List of loot items the player has collected
};

#endif 
