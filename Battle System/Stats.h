#ifndef STATS_H
#define STATS_H

class Stats {
public: 
    Stats(int health, int damage, int defense, int speed);
    
    int getHealth() const;
    int getDamage() const;
    int getDefense() const;
    int getSpeed() const;

    void takeDamage(int damage);

protected:
    int health;
    int damage;
    int defense;
    int speed; 
};

#endif
