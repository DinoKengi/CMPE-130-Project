#include "Map.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <unordered_map>


MapExplore::MapExplore(int numRooms) {
    for (int i = 0; i < numRooms; ++i) {
        rooms.emplace_back("Room " + std::to_string(i));
    }
    startRoom = nullptr;
    endRoom = nullptr;
}


void MapExplore::shuffleRoom() {
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> weightDist(1, 100); // Random weights between 1 and 100

    // Ensure each room is connected to at least one other room
    for (size_t i = 0; i < rooms.size() - 1; ++i) {
        int weight = weightDist(generator);
        rooms[i].addEdge(&rooms[i + 1], weight);
        rooms[i + 1].addEdge(&rooms[i], weight); // Ensure bidirectional connection
    }

    // Add extra random edges for variety
    std::uniform_int_distribution<int> roomDist(0, rooms.size() - 1);
    for (size_t i = 0; i < rooms.size(); ++i) {
        Room* roomA = &rooms[roomDist(generator)];
        Room* roomB = &rooms[roomDist(generator)];
        if (roomA != roomB) { // Avoid self-loops
            int weight = weightDist(generator);
            roomA->addEdge(roomB, weight);
            roomB->addEdge(roomA, weight); // Ensure bidirectional connection
        }
    }

    std::cout << "Rooms and edges randomized.\n";
}

void MapExplore::genTree() {
    if (rooms.empty()) {
        std::cerr << "Error: No rooms to generate MST.\n";
        return;
    }

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    std::set<Room*> visited;
    mstEdges.clear(); // Clear MST edges

    visited.insert(&rooms[0]); // Start with the first room

    for (const auto& edge : rooms[0].getEdges()) {
        pq.push(Edge(&rooms[0], edge.first, edge.second));
    }

    while (!pq.empty()) {
        Edge current = pq.top();
        pq.pop();

        if (visited.find(current.to) != visited.end()) continue;

        visited.insert(current.to);
        mst.emplace_back(current); // Add edge to MST

        // Track edges in MST for each room
        mstEdges[current.from].emplace_back(current.to);
        mstEdges[current.to].emplace_back(current.from);

        std::cout << "Connecting " << current.from->getDesc() << " to " << current.to->getDesc()
                  << " with weight " << current.weight << "\n";

        for (const auto& edge : current.to->getEdges()) {
            if (visited.find(edge.first) == visited.end()) {
                pq.push(Edge(current.to, edge.first, edge.second));
            }
        }
    }

    if (visited.size() != rooms.size()) {
        std::cerr << "Error: MST could not connect all rooms.\n";
        return;
    }

    std::cout << "MST successfully generated.\n";
}



std::pair<Room*, int> MapExplore::findFarthestNode(Room* startRoom) {
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

#include <queue>
#include <unordered_map>

void MapExplore::startPlayerRoute() {
    if (mstEdges.empty()) {
        std::cerr << "Error: MST is empty. Cannot traverse.\n";
        return;
    }

    Room* startLeaf = nullptr;

    // Find a leaf node as the starting point
    for (const auto& [room, edges] : mstEdges) {
        if (edges.size() == 1) { // Leaf nodes have one MST edge
            startLeaf = room;
            break;
        }
    }

    if (!startLeaf) {
        std::cerr << "No leaf nodes found in MST. Map is empty or invalid.\n";
        return;
    }

    std::cout << "Starting traversal at: " << startLeaf->getDesc() << "\n";

    bfsTraversal(startLeaf);
}

// Perform BFS traversal on the MST
void MapExplore::bfsTraversal(Room* start) {
    std::queue<Room*> q;
    std::unordered_map<Room*, bool> visited;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        Room* current = q.front();
        q.pop();

        // Visit the current room
        std::cout << "Player visits: " << current->getDesc() << "\n";

        // Add neighbors in the MST to the queue
        for (Room* neighbor : mstEdges[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
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
    return rooms;
}

