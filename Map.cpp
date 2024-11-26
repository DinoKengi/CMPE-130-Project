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
    std::uniform_int_distribution<int> weightDist(1, 30); // random weights between 1 and 30
    std::uniform_int_distribution<int> encounterDist(0, 1); // Monster or Buff
    std::uniform_int_distribution<int> monsterDist(0, 4); // one of the 5 monsters we got

    for (size_t i = 0; i < rooms.size() - 1; ++i) {
        int weight = weightDist(generator);
        rooms[i].addEdge(&rooms[i + 1], weight);
        rooms[i + 1].addEdge(&rooms[i], weight); // Ensure bidirectional connection
    }

    for (auto& room : rooms) {
        int encounterType = encounterDist(generator);

        if (encounterType == 0) { // MonsterEncounter
            // Randomly select a monster type
            std::unique_ptr<Monster> monster;
            switch (monsterDist(generator)) {
                case 0: monster = std::make_unique<Goblin>(); break;
                case 1: monster = std::make_unique<Slime>(); break;
                case 2: monster = std::make_unique<Ogre>(); break;
                case 3: monster = std::make_unique<Bandit>(); break;
                case 4: monster = std::make_unique<Ghost>(); break;
                default: monster = std::make_unique<Goblin>(); break; // Fallback
            }

            room.setEncounter(std::make_unique<MonsterEncounter>(std::move(monster)));

        } else if (encounterType == 1) { // BuffEncounter
            room.setEncounter(std::make_unique<BuffEncounter>(Buff("Damage Boost", 10))); // Example buff

        }
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

void MapExplore::startPlayerRoute(Player& player) {
    if (mstEdges.empty()) {
        std::cerr << "Error: MST is empty. Cannot traverse.\n";
        return;
    }

    // Identify all leaf nodes (rooms with one MST connection)
    std::vector<Room*> leafNodes;
    for (const auto& [room, edges] : mstEdges) {
        if (edges.size() == 1) {
            leafNodes.push_back(room);
        }
    }

    if (leafNodes.empty()) {
        std::cerr << "No leaf nodes found in MST. Cannot start traversal.\n";
        return;
    }

    // Randomly select a starting leaf node
    std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, leafNodes.size() - 1);
    Room* startRoom = leafNodes[dist(generator)];

    std::cout << "Starting traversal at: " << startRoom->getDesc() << "\n";

    // Find the farthest node from the starting leaf
    auto [farthestNode, distance] = findFarthestNode(startRoom);
    if (!farthestNode) {
        std::cerr << "Error finding farthest node.\n";
        return;
    }

    std::cout << "Farthest node is: " << farthestNode->getDesc()
              << " at a distance of " << distance << "\n";

    // Traverse the path from start to farthest node
    traverse(startRoom, farthestNode, player);

    if (player.isAlive()) {
        std::cout << "\nYou reach the final room...\n";
        finalBossEncounter(player);
    } else {
        std::cout << "\nYou did not survive the dungeon to face the final boss.\n";
    }
}


void MapExplore::traverse(Room* startRoom, Room* endRoom, Player& player) {
    std::unordered_map<Room*, Room*> parent;
    std::queue<Room*> q;

    q.push(startRoom);
    parent[startRoom] = nullptr; // Mark the root node

    // BFS to find the path from startRoom to endRoom
    while (!q.empty()) {
        Room* current = q.front();
        q.pop();

        if (current == endRoom) break;

        for (Room* neighbor : mstEdges[current]) {
            if (!parent.count(neighbor)) { // If not visited
                parent[neighbor] = current;
                q.push(neighbor);
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

    // Guide the player through the path and trigger encounters
    std::cout << "\nPlayer's Path:\n";
    for (Room* room : path) {
        std::cout << "Player visits: " << room->getDesc() << "\n";
        room->triggerEncounter(player);

        if (!player.isAlive()) {
            std::cout << player.getName() << " has fallen in battle...\n";
            break;
        }
    }
}


// void MapExplore::finalBossEncounter(Player& player) {
//     std::cout << "\nA massive roar echoes through the dungeon...\n";
//     std::cout << "The Dragon emerges to challenge you!\n";

//     Dragon dragon;

//     // Simple battle loop for the final boss
//     while (player.isAlive() && dragon.isAlive()) {
//         // Player attacks Dragon
//         dragon.takeDamage(player.getDamage());
//         std::cout << player.getName() << " attacks Dragon for " << player.getDamage() << " damage.\n";

//         if (!dragon.isAlive()) {
//             std::cout << "The Dragon has been defeated! You are victorious!\n";
//             break;
//         }

//         // Dragon attacks Player
//         player.takeDamage(dragon.getDamage());
//         std::cout << "The Dragon attacks " << player.getName()
//                   << " for " << dragon.getDamage() << " damage.\n";

//         if (!player.isAlive()) {
//             std::cout << player.getName() << " has fallen in battle...\n";
//             break;
//         }
//     }
// }

void MapExplore::finalBossEncounter(Player& player) {
    std::cout << "\nA massive roar echoes through the dungeon...\n";
    std::cout << "The Dragon emerges to challenge you!\n";

    Dragon dragon;
    int turnCounter = 0; // Counter to track the number of turns

    // Battle loop
    while (player.isAlive() && dragon.isAlive()) {
        // Player's turn
        turnCounter++; // Increment turn counter
        std::cout << "\nYour turn! Choose an action:\n";
        std::cout << "1. Attack\n";
        std::cout << "2. Block\n";
        std::cout << "3. Rest (restore some health)\n";
        if (turnCounter >= 3) { // Enable strong attack after every 3 turns
            std::cout << "4. Strong Attack (3x damage!)\n";
        }

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: { // Regular Attack
                int damageToDragon = player.getDamage();
                dragon.takeDamage(damageToDragon);
                std::cout << player.getName() << " attacks Dragon for " << damageToDragon << " damage.\n";
                break;
            }
            case 2: { // Block
                std::cout << player.getName() << " braces for the Dragon's attack.\n";
                player.setDefense(player.getDefense() + 10); // Temporary defense boost
                break;
            }
            case 3: { // Rest
                int healAmount = 20; // Example: Restore 20 health
                player.setHealth(player.getHealth() + healAmount);
                std::cout << player.getName() << " rests and recovers " << healAmount << " health.\n";
                break;
            }
            case 4: { // Strong Attack (only available after 3 turns)
                if (turnCounter >= 3) {
                    int strongDamage = player.getDamage() * 3; // 3x damage
                    dragon.takeDamage(strongDamage);
                    std::cout << player.getName() << " unleashes a powerful attack on Dragon for " << strongDamage << " damage!\n";
                    turnCounter = 0; // Reset counter after strong attack
                } else {
                    std::cout << "Strong Attack is not available yet. Try again.\n";
                    turnCounter--; // Do not count this as a valid turn
                }
                break;
            }
            default:
                std::cout << "Invalid choice! The Dragon takes advantage of your hesitation.\n";
                break;
        }

        // Check if Dragon is defeated
        if (!dragon.isAlive()) {
            std::cout << "The Dragon has been defeated! You are victorious!\n";
            break;
        }

        // Dragon's turn
        int damageToPlayer = dragon.getDamage() - player.getDefense();
        if (damageToPlayer < 0) damageToPlayer = 0; // Prevent negative damage
        player.takeDamage(damageToPlayer);
        std::cout << "The Dragon attacks " << player.getName() << " for " << damageToPlayer << " damage.\n";

        // Reset player's temporary defense boost
        if (choice == 2) {
            player.setDefense(player.getDefense() - 10);
        }

        // Check if Player is defeated
        if (!player.isAlive()) {
            std::cout << player.getName() << " has fallen in battle...\n";
            break;
        }
    }
}




std::vector<Room>& MapExplore::getRooms() {
    return rooms;
}

