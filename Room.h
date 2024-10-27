#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Loot.h"

class Room {
public:
    Room(std::string description);

    // set rooms next to each other
    void setAdjacentRoom(const std::string& direction, Room* adjacentRoom);

    // accessor
    Room* getAdjacentRoom(const std::string& direction);
    std::string getDescription() const;
    
    // loot handling
    void addLoot(Loot lootItem);
    const std::vector<Loot>& getLoot() const;
    bool hasLoot() const;

private:
    std::string description;
    std::unordered_map<std::string, Room*> adjacentRooms; // maps directions to rooms
    std::vector<Loot> loot;  // list of loot in room
};

#endif 
