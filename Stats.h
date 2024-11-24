#ifndef STATS_H
#define STATS_H

class Stats {
public:
    Stats(int health, int damage, int defense, int speed);

    // Getter functions
    int getHealth() const;
    int getDamage() const;
    int getDefense() const;
    int getSpeed() const;

    // Setter functions
    void setHealth(int health);
    void setDamage(int damage);
    void setDefense(int defense);
    void setSpeed(int speed);

    // Utility functions for adjustments
    void increaseHealth(int amount);
    void increaseDamage(int amount);
    void increaseDefense(int amount);

    void takeDamage(int damage);

private:
    int health;
    int damage;
    int defense;
    int speed;
};

#endif
