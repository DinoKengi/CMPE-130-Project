#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include "ROOM.H"

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
    Room* startRoom; // starting room
    Room* endRoom; // farthest room from start

    // algorithms
    void genPrim();
    // player traversal routes
    void traverse(Room* startRoom, Room* endRoom); // guide for playuer along path
};

#endif 
