#ifndef LOOT_H
#define LOOT_H

#include <string>

class Loot {
public:
    Loot(std::string name);

    std::string getName() const;

private:
    std::string name;  // item name
};

#endif
