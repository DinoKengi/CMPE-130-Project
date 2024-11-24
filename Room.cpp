#include "Room.h"
#include <iostream>

Room::Room(const std::string& desc)
    : desc(desc), roomBuff(nullptr) {}

void Room::setBuff(const Buff& buff) {
    roomBuff = new Buff(buff);
}

bool Room::hasBuff() const {
    return roomBuff != nullptr;
}

void Room::giveBuff(Player& player) {
    if (roomBuff) {
        roomBuff->applyTo(player); // Apply the buff to the player
        delete roomBuff;          // Remove the buff from the room (applied once)
        roomBuff = nullptr;
    }
}

void Room::setEncounter(std::unique_ptr<Encounter> encounter) {
    this->encounter = std::move(encounter); // Transfer ownership
}

void Room::triggerEncounter(Player& player) {
    if (encounter) {
        encounter->trigger(player);
    } else {
        std::cout << "No encounter in this room.\n";
    }
}

void Room::addEdge(Room* room, int weight) {
    edges.emplace_back(room, weight);
}

std::vector<std::pair<Room*, int>> Room::getEdges() const {
    return edges;
}

std::string Room::getDesc() const {
    return desc;
}
