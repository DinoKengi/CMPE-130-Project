#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include "ROOM.H"

class Room {
public:
    Room(const std:: string& desc) : desc(desc) {} // initialize room with a description

    void addEdge(Room* room, int weight); // edge connection 
    std::vector<std::pair<Room*, int>> getEdges() const;

    std::string getDesc() const { return desc; }

private: 
    std::string desc;
    std::vector<std::pair<Room*, int>> edges; // connected rooms and weights
};

class MapExplore {
public:
    MapExplore(int numRooms); // this will help us create list of rooms based on # of rooms
    void genTree(bool useKruskal = false); // option between prim or kruskal

    Room* getStart() const; 
    void addRoom(int id, const Room& room);
    Room* getRoom(int id);

private:
    std::vector<Room> room;
    Room* startRoom;

    void genPrim();
    void genKrus();
    void shuffleRoom();
};

#endif 
