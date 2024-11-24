#include "Encounter.h"
#include <cstdlib> // For rand()
#include <ctime>   // For srand

RandomEncounter::RandomEncounter() {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed for random number generation
}

int RandomEncounter::getRandomNumber(int min, int max) {
    return std::rand() % (max - min + 1) + min;
}

std::string RandomEncounter::makeEncounter() {
    int random = getRandomNumber(1, 5); // Adjust range based on monster types

    switch (random) {
        case 1: return "Goblin";
        case 2: return "Slime";
        case 3: return "Ogre";
        case 4: return "Bandit";
        case 5: return "Ghost";
        default: return "Goblin"; // Fallback in case of error
    }
}
