#ifndef BUFF_H
#define BUFF_H

#include <string>

class Player; // Forward declaration

class Buff {
public:
    Buff(const std::string& description, int value);

    std::string getDescription() const;
    void applyTo(Player& player) const; // Apply the buff to the player

private:
    std::string description; // e.g., "+1 damage"
    int value; // Effect value
};

#endif
