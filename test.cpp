#include "Player.h"
#include "Buff.h"
#include "Room.h"
#include "Map.h"
#include "Story.h"
#include "Stats.h"
#include <iostream>

int main() {
    // Test Player
    Wizard player("Merlin");
    std::cout << "Player created: " << player.getName() << " (Class: " << player.getClassType() << ")\n";
    std::cout << "Stats - Health: " << player.getHealth()
              << ", Damage: " << player.getDamage()
              << ", Defense: " << player.getDefense() << "\n";

    // Test Buff System
    Buff healthBuff("Health Boost", 20);
    Buff damageBuff("Damage Boost", 10);

    std::cout << "\nApplying Buff: " << healthBuff.getDesc() << "\n";
    healthBuff.applyTo(player);
    std::cout << "Player health after buff: " << player.getHealth() << "\n";

    std::cout << "\nApplying Buff: " << damageBuff.getDesc() << "\n";
    damageBuff.applyTo(player);
    std::cout << "Player damage after buff: " << player.getDamage() << "\n";

    // Test Map and Prim's Algorithm
    // MapExplore map(8);         // Create a map with 8 rooms
    // map.shuffleRoom();         // Randomize room connections and weights
    // std::cout << "\nGenerating Minimum Spanning Tree using Prim's Algorithm...\n";
    //map.genTree();             // Generate MST
    // std::cout << "\nPlayer traverses the map:\n";
    // map.startPlayerRoute();    // Start player traversal

    // Debugging: Print the randomized graph
    // for (size_t i = 0; i < map.getRooms().size(); i++) {
    //    std::cout << "Room " << i << " connections: ";
    //    for (const auto& edge : map.getRooms()[i].getEdges()) {
    //        std::cout << " -> " << edge.first->getDesc() << " (Weight: " << edge.second << ")";
    //    }
    //    std::cout << "\n";
    // }

    return 0;
}
