#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <unordered_map> // For std::unordered_map
#include "Room.h"

class Room;

// Define the Edge struct
struct Edge {
    Room* from; // Source room
    Room* to;   // Destination room
    int weight; // Weight of the edge

    Edge(Room* from, Room* to, int weight)
        : from(from), to(to), weight(weight) {}

    // Comparator for priority queue
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

class MapExplore {
public:
    MapExplore(int numRooms); // this will help us create list of rooms based on # of rooms
    void genTree(); // option between prim or kruskal
    void startPlayerRoute(Player& player);
    void shuffleRoom();
    void finalBossEncounter(Player& player); // Final boss encounter function
    std::pair<Room*, int> findFarthestNode(Room* startRoom); // this for farthest node


    std::vector<Room>& getRooms();

private:
    std::vector<Room> rooms; // room storage
    std::vector<Edge> mst;
    std::unordered_map<Room*, std::vector<Room*>> mstEdges; // Tracks MST connections

    Room* startRoom; // starting room
    Room* endRoom; // farthest room from start

    // player traversal routes
    void traverse(Room* startRoom, Room* endRoom, Player& player); // guide for playuer along path
};

#endif 
