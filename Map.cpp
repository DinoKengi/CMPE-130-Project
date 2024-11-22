#include "Map.h"
#include <iostream>
#include <random>
#include <unordered_map>

struct Edge {
    Room* room1;
    Room* room2;
    int weight;
};

void Room::addEdge(Room* room, int weight) {
    edges.emplace_back(room, weight);
}

std::vector<std::pair<Room*, int>> Room::getEdges() const {
    return edges;
}

MapExplore::MapExplore(int numRooms) {
    for (int i = 0; i < numRooms; ++i) {
        room.emplace_back("Room " + std::to_string(i));
    }
    genTree(); // default to Prim's algorithm
}

void MapExplore::shuffleRoom() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(room.begin(), room.end(), g);
}

void MapExplore::genTree(bool useKruskal) {
    shuffleRoom();
    startRoom = &room[0];
    if (useKruskal) {
        genKrus();
    } else {
        genPrim();
    }
}

void MapExplore::genPrim() {
    std::priority_queue<std::pair<int, Room*>, std::vector<std::pair<int, Room*>>, std::greater<>> pq;
    std::set<Room*> visited;

    pq.push({0, startRoom});

    while (!pq.empty()) {
        auto [weight, current] = pq.top();
        pq.pop();

        if (visited.count(current)) continue;
        visited.insert(current);

        for (const auto& conn : current->getEdges()) {
            if (!visited.count(conn.first)) {
                pq.push({conn.second, conn.first});
            }
        }
    }
}

void MapExplore::genKrus() {
    std::vector<Edge> edges;
    for (auto& room : room) {
        for (const auto& conn : room.getEdges()) {
            edges.push_back({&room, conn.first, conn.second});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    std::unordered_map<Room*, Room*> parent; 
    for (auto& room : room) {
        parent[&room] = &room; // Initialize parent pointers
    }

    auto find = [&](Room* room, auto& self) -> Room* {
        if (parent[room] == room) return room;
        return parent[room] = self(parent[room], self); // Path compression
    };

    for (const auto& edge : edges) {
        Room* root1 = find(edge.room1, find);
        Room* root2 = find(edge.room2, find);

        if (root1 != root2) {
            parent[root1] = root2;
            edge.room1->addEdge(edge.room2, edge.weight);
            edge.room2->addEdge(edge.room1, edge.weight);
        }
    }
}



Room* MapExplore::getStart() const {
    return startRoom;
}
