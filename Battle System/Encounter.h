#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <string>

class RandomEncounter {
public:
    RandomEncounter();
    
    std::string makeEncounter(); // returns a random encounter description

private:
    int getRandomNumber(int min, int max); // helper function to get a random number
};

#endif 
