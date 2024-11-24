#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <utility> // for std::pair
#include <memory>
#include "Buff.h"
#include "Player.h"
#include "Encounter.h"

class Room {
public:
    Room(const std::string& desc);

    void setBuff(const Buff& buff);
    bool hasBuff() const;
    void giveBuff(Player& player); // if player comes into buff room then give buff

    void addEdge(Room* room, int weight);  // add edge to a node
    std::vector<std::pair<Room*, int>> getEdges() const;

    std::string getDesc() const; // room desc

    void setEncounter(std::unique_ptr<Encounter> encounter);
    void triggerEncounter(Player& player);

private:
    std::string desc; // room description
    Buff* roomBuff; 
    std::vector<std::pair<Room*, int>> edges; // connections to other rooms
    std::unique_ptr<Encounter> encounter; // encounter in room
};

#endif
