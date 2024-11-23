#ifndef STATS_H
#define STATS_H

class Stats {
public:
    Stats(int health, int damage, int defense);

    // Getter functions
    int getHealth() const;
    int getDamage() const;
    int getDefense() const;

    // Setter functions
    void setHealth(int health);
    void setDamage(int damage);
    void setDefense(int defense);

    // Utility functions for adjustments
    void increaseHealth(int amount);
    void increaseDamage(int amount);
    void increaseDefense(int amount);

private:
    int health;
    int damage;
    int defense;
};

#endif
