#include "Room.h"

Room::Room(std::string description)
    : description(description) {}

void Room::setAdjacentRoom(const std::string& direction, Room* adjacentRoom) {
    adjacentRooms[direction] = adjacentRoom;
}

Room* Room::getAdjacentRoom(const std::string& direction) {
    if (adjacentRooms.find(direction) != adjacentRooms.end()) {
        return adjacentRooms[direction];
    }
    return nullptr; // return nullptr if no room in that direction
}

std::string Room::getDescription() const {
    return description;
}

void Room::addLoot(Loot lootItem) {
    loot.push_back(lootItem);
}

const std::vector<Loot>& Room::getLoot() const {
    return loot;
}

bool Room::hasLoot() const {
    return !loot.empty();
}
