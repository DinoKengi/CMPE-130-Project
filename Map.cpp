#include "Map.h"
#include <iostream>
#include <random>
#include <unordered_map>


MapExplore::MapExplore(int numRooms) {
    for (int i = 0; i < numRooms; ++i) {
        room.emplace_back("Room " + std::to_string(i));
    }
    startRoom = nullptr;
    endRoom = nullptr;
}


void MapExplore::shuffleRoom() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(room.begin(), room.end(), g);
}

void MapExplore::genTree() {
    if (room.empty()) {
        std::cerr << "Error: No rooms to generate MST.\n";
        return;
    }

    // Priority queue for edges with smallest weight first
    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    std::set<Room*> visited;

    // Start with the first room
    visited.insert(&room[0]);

    // Add edges of the first room to the queue
    for (const auto& edge : room[0].getEdges()) {
        pq.push(Edge(&room[0], edge.first, edge.second)); // Convert std::pair to Edge
    }

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        if (visited.find(current.to) != visited.end()) continue;

        visited.insert(current.to);
        mst.emplace_back(current);

        std::cout << "Connecting " << current.from->getDesc() << " to " << current.to->getDesc() << "\n";

        for (const auto& edge : current.to->getEdges()) {
            if (visited.find(edge.first) == visited.end()) {
                pq.push(Edge(current.to, edge.first, edge.second));
            }
        }
    }

    if (visited.size() != room.size()) {
        std::cerr << "Error: MST could not connect all rooms.\n";
        return;
    }

    std::cout << "MST successfully generated.\n";
}




std::pair<Room*, int> MapExplore::findfarthestNode(Room* startRoom) {
    std::queue<std::pair<Room*, int>> q; // Pair: Room and distance from start
    std::unordered_map<Room*, bool> visited;
    Room* farthestNode = startRoom;
    int maxDistance = 0;

    q.push({startRoom, 0});
    visited[startRoom] = true;

    while (!q.empty()) {
        auto [currentRoom, currentDistance] = q.front();
        q.pop();

        // update farthest node if a greater distance is found
        if (currentDistance > maxDistance) {
            maxDistance = currentDistance;
            farthestNode = currentRoom;
        }

        // add neighbors to the queue
        for (const auto& connection : currentRoom->getEdges()) {
            Room* nextRoom = connection.first;
            int edgeWeight = connection.second;

            if (!visited[nextRoom]) {
                visited[nextRoom] = true;
                q.push({nextRoom, currentDistance + edgeWeight});
            }
        }
    }

    return {farthestNode, maxDistance};
}

void MapExplore::startPlayerRoute() {
    // Identify a leaf node
    Room* startLeaf = nullptr;
    for (auto& room : room) {
        if (room.getEdges().size() == 1) { // Leaf nodes have 1 connection
            startLeaf = &room;
            break;
        }
    }

    if (!startLeaf) {
        std::cout << "No leaf nodes found. Map is empty or invalid." << std::endl;
        return;
    }

    // Find the farthest node from the starting leaf node
    auto [farthestNode, distance] = findfarthestNode(startLeaf);
    endRoom = farthestNode;

    std::cout << "Starting at: " << startLeaf->getDesc() << std::endl;
    std::cout << "Farthest node is: " << farthestNode->getDesc()
              << " at a distance of " << distance << std::endl;

    // Guide the player along the path
    std::cout << "Guiding player from start to farthest node..." << std::endl;
    traverse(startLeaf, farthestNode);
}

void MapExplore::traverse(Room* startRoom, Room* endRoom) {
    std::unordered_map<Room*, Room*> parent;
    std::queue<Room*> q;

    q.push(startRoom);
    parent[startRoom] = nullptr; // Mark the root node

    // BFS to find the path from startRoom to endRoom
    while (!q.empty()) {
        Room* current = q.front();
        q.pop();

        if (current == endRoom) break;

        for (const auto& connection : current->getEdges()) {
            Room* nextRoom = connection.first;

            if (!parent.count(nextRoom)) { // If not visited
                parent[nextRoom] = current;
                q.push(nextRoom);
            }
        }
    }

    // Backtrack from endRoom to startRoom to trace the path
    Room* current = endRoom;
    std::vector<Room*> path;
    while (current) {
        path.push_back(current);
        current = parent[current];
    }

    // Reverse the path to get start-to-end order
    std::reverse(path.begin(), path.end());

    // Guide the player
    for (Room* room : path) {
        std::cout << "Player visits: " << room->getDesc() << std::endl;
    }
}


Room* MapExplore::getStart() const {
    return startRoom;
}

std::vector<Room>& MapExplore::getRooms() {
    return room;
}

