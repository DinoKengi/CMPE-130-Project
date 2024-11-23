#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include "ROOM.H"

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

    Room* getStart() const;  // start room (start node)
    Room* getEnd() const; // farthest node (end room)
    void startPlayerRoute();
    void shuffleRoom();
    std::pair<Room*, int> findfarthestNode(Room* startRoom); // this for farthest node


    std::vector<Room>& getRooms();

private:
    std::vector<Room> room; // room storage
    std::vector<Edge> mst;
    Room* startRoom; // starting room
    Room* endRoom; // farthest room from start

    // player traversal routes
    void traverse(Room* startRoom, Room* endRoom); // guide for playuer along path
};

#endif 
