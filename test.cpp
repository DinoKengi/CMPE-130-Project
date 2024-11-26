#include "Player.h"
#include "Map.h"
#include <iostream>
#include <memory>

int main() {
    // Welcome message
    std::cout << "Welcome to the Dungeon Adventure!\n";
    std::cout << "Prepare to explore the dungeon, face dangerous monsters, and defeat the final boss.\n";

    // Get player's name
    std::cout << "\nEnter your name: ";
    std::string playerName;
    std::cin.ignore(); // Clear previous input
    std::getline(std::cin, playerName);

    // Choose a class
    std::cout << "\nChoose your class:\n";
    std::cout << "1. Knight\n";
    std::cout << "2. Wizard\n";
    std::cout << "3. Archer\n";
    int choice;
    std::cin >> choice;

    std::unique_ptr<Player> player;

    switch (choice) {
        case 1:
            player = std::make_unique<Knight>(playerName);
            break;
        case 2:
            player = std::make_unique<Wizard>(playerName);
            break;
        case 3:
            player = std::make_unique<Archer>(playerName);
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Knight.\n";
            player = std::make_unique<Knight>(playerName);
            break;
    }

    // Display player stats
    std::cout << "\nPlayer created: " << player->getName() << " (Class: " << player->getClassType() << ")\n";
    std::cout << "Stats - Health: " << player->getHealth()
              << ", Damage: " << player->getDamage()
              << ", Defense: " << player->getDefense() << "\n";

    // Create and set up the dungeon
    MapExplore map(8); // Example map with 8 rooms
    map.shuffleRoom(); // Randomize the rooms and encounters

    // Generate the MST to connect rooms
    std::cout << "\nGenerating Minimum Spanning Tree...\n";
    map.genTree();

    // Find the farthest node and display the distance
    Room* startRoom = &map.getRooms().front(); // Use the first room as the starting point
    auto [farthestNode, distance] = map.findFarthestNode(startRoom);

    std::cout << "\nFarthest node is: " << farthestNode->getDesc()
              << " at a distance of " << distance << "\n";

    // Traverse through the rooms
    auto& rooms = map.getRooms();
    std::cout << "\nStarting Player Route:\n";

    for (Room& room : rooms) {
        if (!player->isAlive()) {
            std::cout << player->getName() << " has fallen in battle...\n";
            break;
        }

        // Enter the room and trigger the encounter
        std::cout << "You are in: " << room.getDesc() << "\n";
        room.triggerEncounter(*player);

        if (!player->isAlive()) {
            std::cout << "You were defeated in the dungeon. Game Over.\n";
            return 0;
        }

        // Ask player if they want to rest after the fight
        if (&room != &rooms.back()) { // Only offer rest if this isn't the final room
            
                std::cout << "\nThe room is quiet now. Would you like to rest?\n";
                std::cout << "1. Yes (Restore 20 health)\n";
                std::cout << "2. No (Continue to the next room)\n";

                int restChoice;
                std::cin >> restChoice;

                if (restChoice == 1) {
                    int healAmount = 20;
                    player->setHealth(player->getHealth() + healAmount);
                    std::cout << "You rest and recover " << healAmount << " health. Current health: " << player->getHealth() << "\n";
                } else if (restChoice == 2) {
                    std::cout << "You decide to move on to the next room.\n";
                    break; // Exit the loop
                } else {
                    std::cout << "Invalid choice. Please select 1 to rest or 2 to continue.\n";
                }
            
        }
    }

    // Final Boss Battle
    if (player->isAlive()) {
        std::cout << "\nYou reach the final room...\n";
        map.finalBossEncounter(*player);
    }

    // End of the game
    if (player->isAlive()) {
        std::cout << "\nCongratulations! You have cleared the dungeon and defeated the final boss!\n";
    } else {
        std::cout << "\nGame Over. Better luck next time!\n";
    }

    return 0;
}
