#include "Player.h"
#include "Buff.h"
#include "Room.h"
#include "Map.h"
#include "Story.h"
#include "Stats.h"
#include <iostream>

int main() {
    // 1. Test Player and Stats
    Wizard player("Merlin"); // Using Wizard as a subclass of Player
    std::cout << "Player created: " << player.getName() << " (Class: " << player.getClassType() << ")\n";
    std::cout << "Stats - Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";

    // 2. Test Buff System
    Buff healthBuff("Health Boost", 20);
    Buff damageBuff("Damage Boost", 10);

    std::cout << "\nApplying Buff: " << healthBuff.getDesc() << "\n";
    healthBuff.applyTo(player);
    std::cout << "Player health after buff: " << player.getHealth() << "\n";

    std::cout << "\nApplying Buff: " << damageBuff.getDesc() << "\n";
    damageBuff.applyTo(player);
    std::cout << "Player damage after buff: " << player.getDamage() << "\n";

    // 3. Test Room Connections and Buff Application
    Room room1("Start Room");
    Room room2("Buff Room");
    Room room3("Battle Room");

    room1.addEdge(&room2, 5);
    room2.addEdge(&room3, 10);

    std::cout << "\nRoom Connections:\n";
    std::cout << room1.getDesc() << " -> " << room2.getDesc() << " (Weight: 5)\n";
    std::cout << room2.getDesc() << " -> " << room3.getDesc() << " (Weight: 10)\n";

    room2.setBuff(healthBuff);
    std::cout << "\nPlayer enters " << room2.getDesc() << "\n";
    room2.giveBuff(player);
    std::cout << "Player health after entering room: " << player.getHealth() << "\n";

    // 4. Test Map and Prim's Algorithm
    MapExplore map(8);

    map.getRooms()[0].addEdge(&map.getRooms()[1], 5);
    map.getRooms()[1].addEdge(&map.getRooms()[2], 10);
    map.getRooms()[2].addEdge(&map.getRooms()[3], 15);
    map.getRooms()[3].addEdge(&map.getRooms()[4], 20);
    map.getRooms()[4].addEdge(&map.getRooms()[5], 25);
    map.getRooms()[5].addEdge(&map.getRooms()[6], 30);
    map.getRooms()[6].addEdge(&map.getRooms()[7], 35);
    map.getRooms()[7].addEdge(&map.getRooms()[0], 40); // Add a loop for full connectivity

    
    map.shuffleRoom();
    std::cout << "\nGenerating Minimum Spanning Tree using Prim's Algorithm...\n";
    map.genTree();
    std::cout << "\nPlayer traverses the map:\n";
    map.startPlayerRoute();

    for (size_t i = 0; i < map.getRooms().size(); i++) {
        std::cout << "Room " << i << " connections: ";
        for (const auto& edge : map.getRooms()[i].getEdges()) {
            std::cout << " -> " << edge.first->getDesc() << " (Weight: " << edge.second << ")";
        }
        std::cout << "\n";
    }
    
    return 0;
}
