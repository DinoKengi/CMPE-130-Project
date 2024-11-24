#ifndef MONSTERS_H
#define MONSTERS_H

#include "Stats.h"
#include <string>
#include <iostream> // Required for std::cout and std::endl

class Monster : public Stats {
public:
    Monster(const std::string& name, int health, int damage, int defense, const std::string& story)
        : Stats(health, damage, defense), name(name), encounterStory(story) {}

    virtual void attack() = 0; // Each monster has its own attack behavior

    bool isAlive() const { 
        return getHealth() > 0; 
    }

    std::string getName() const { 
        return name; 
    }

    void displayEncounterStory() const { 
        std::cout << encounterStory << std::endl; 
    }

protected:
    std::string name;
    std::string encounterStory; // Unique story for each monster encounter
};

// Ogre Monster
class Ogre : public Monster {
public:
    Ogre()
        : Monster("Ogre", 100, 20, 5,
                  "You smell a bad odor coming out of a cave, as you hear a scream of an Ogre come out of the cave.") {}
    void attack() override {
        std::cout << "The big fat Ogre swings his club against you!" << std::endl;
    }
};

// Goblin Monster
class Goblin : public Monster {
public:
    Goblin()
        : Monster("Goblin", 40, 10, 2,
                  "A sneaky Goblin jumps out of the shadows!") {}
    void attack() override {
        std::cout << "The Goblin slashes at you with a rusty dagger!" << std::endl;
    }
};

// Slime Monster
class Slime : public Monster {
public:
    Slime()
        : Monster("Slime", 30, 5, 1,
                  "As you walk, you feel the ground really sticky. A hopping slime has jumped in front of you.") {}
    void attack() override {
        std::cout << "The slime squirted at your face!" << std::endl;
    }
};

// Bandit Monster
class Bandit : public Monster {
public:
    Bandit()
        : Monster("Bandit", 70, 15, 5,
                  "A bandit comes out of the shadow threatening you to give all you have!") {}
    void attack() override {
        std::cout << "The bandit lunges towards you with a swift strike!" << std::endl;
    }
};

// Ghost Monster
class Ghost : public Monster {
public:
    Ghost()
        : Monster("Ghost", 50, 15, 2,
                  "You feel an eerie presence as you see books starting to float around you.\nA ghost appears in front of you with YOUR OWN FACE!") {}
    void attack() override {
        std::cout << "The Ghost slashes at you" << std::endl;
    }
};

// Dragon Monster (Final Boss)
class Dragon : public Monster {
public:
    Dragon()
        : Monster("Dragon", 2000, 60, 30,
                  "You approach a fiery cavern...\n"
                  "A powerful presence appears ahead!\n"
                  "A mighty Dragon roars, shaking the ground beneath you!\n"
                  "The Dragon breathes a torrent of fire!\n"
                  "You prepare yourself for the final battle against the mighty Dragon.") {}
    void attack() override {
        std::cout << "The dragon blasts you with a fireball" << std::endl;
    }
};

#endif
