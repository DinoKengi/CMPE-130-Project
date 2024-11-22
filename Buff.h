#ifndef BUFF_H
#define BUFF_H

#include <string>

class Player; // forward declaration

class Buff {
public:
    Buff(const std::string& desc, int value);

    std::string getDesc() const;
    void applyTo(Player& player) const; // apply the buff to the player

private:
    std::string desc; // ex: "+1 damage"
    int value; // effect value
};

#endif
