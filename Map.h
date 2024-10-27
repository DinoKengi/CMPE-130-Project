#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <string>

class Room {
public:
    std::string description;

    Room(const std::string& desc);
};

class MapExplore {
public:
    MapExplore();
    
    void addRoom(int roomID, const Room& room);
    Room* getRoom(int roomID);  // get the room based on route

private:
    std::unordered_map<int, Room> roomMap;
};

#endif 
