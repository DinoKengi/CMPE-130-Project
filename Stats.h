#ifndef STATS_H
#define STATS_H

class Stats {
    public: 
        Stats(int health, int damage, int defense);
        int getHealth() const;
        int getDamage() const;
        int getDefense() const;

    protected:
        int health;
        int damage;
        int defense;
};

#endif