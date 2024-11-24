#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Player.h"
#include "Monster.h"
#include "Buff.h"
#include <string>
#include <memory>

// Abstract Encounter class
class Encounter {
public:
    virtual void trigger(Player& player) = 0; // Trigger the encounter for the player
    virtual ~Encounter() = default; // Virtual destructor for polymorphism
};

// Monster Encounter
class MonsterEncounter : public Encounter {
public:
    explicit MonsterEncounter(std::unique_ptr<Monster> monster); // Constructor
    void trigger(Player& player) override; // Trigger a battle with the monster

private:
    std::unique_ptr<Monster> monster; // The monster for this encounter
};

// Buff Encounter
class BuffEncounter : public Encounter {
public:
    explicit BuffEncounter(const Buff& buff); // Constructor
    void trigger(Player& player) override; // Apply the buff to the player

private:
    Buff buff; // The buff for this encounter
};

#endif // ENCOUNTER_H
