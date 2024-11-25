#include "Player.h"
#include "Map.h"
#include "Room.h"
#include "Buff.h"
#include "Monster.h"
#include "Battle.h"
#include "Encounter.h"
#include <iostream>
#include <string>

int main() {
    // Welcome message
    std::cout << "=====================================\n";
    std::cout << "       Welcome to the Adventure!     \n";
    std::cout << "=====================================\n";
    std::cout << "Embark on a journey through a perilous dungeon filled with monsters and treasures.\n";
    std::cout << "You will face dangerous foes, collect buffs, and fight for survival.\n\n";

    // Map randomization
    std::cout << "Randomizing the dungeon layout...\n";
    MapExplore map(5);  // Create a map with 5 rooms
    map.shuffleRoom();  // Randomize room connections and encounters
    map.genTree();      // Generate a minimum spanning tree
    std::cout << "The dungeon is ready. Prepare to enter!\n\n";

    // Set the final room as the Dragon's lair
    auto& rooms = map.getRooms();
    Room* finalRoom = &rooms.back(); // The last room
    finalRoom->setEncounter(std::make_unique<MonsterEncounter>(std::make_unique<Dragon>()));

    // Character creation
    std::string playerName;
    int classChoice;
    std::cout << "Enter your character's name: ";
    std::getline(std::cin, playerName);

    std::cout << "Choose your class:\n";
    std::cout << "1. Wizard - High damage, low defense.\n";
    std::cout << "2. Knight - Balanced stats.\n";
    std::cout << "3. Archer - Agile and precise.\n";
    std::cout << "Enter your choice (1/2/3): ";
    std::cin >> classChoice;

    Player* player = nullptr;
    switch (classChoice) {
        case 1:
            player = new Wizard(playerName);
            break;
        case 2:
            player = new Knight(playerName);
            break;
        case 3:
            player = new Archer(playerName);
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Knight.\n";
            player = new Knight(playerName);
            break;
    }

    std::cout << "\nWelcome, " << player->getName() << " the " << player->getClassType() << "!\n";
    std::cout << "Starting Stats - Health: " << player->getHealth()
              << ", Damage: " << player->getDamage()
              << ", Defense: " << player->getDefense() << "\n\n";

    // Interactive dungeon exploration
    size_t roomIndex = 0;

    while (player->isAlive() && roomIndex < rooms.size()) {
        Room* currentRoom = &rooms[roomIndex];

        std::cout << "\nYou are in: " << currentRoom->getDesc() << "\n";
        if (roomIndex == rooms.size() - 1) {
            std::cout << "You feel a powerful presence... This is the Dragon's lair!\n";
        }

        std::cout << "What would you like to do?\n";
        std::cout << "1. Explore this room\n";
        std::cout << "2. Skip to the next room\n";
        std::cout << "3. Rest and regain some health\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            currentRoom->triggerEncounter(*player);

            // Check if the player survived the encounter
            if (!player->isAlive()) {
                std::cout << "You have perished in the dungeon. Game over!\n";
                break;
            }

            // Display updated stats
            std::cout << "\nPlayer Stats After Encounter:\n";
            std::cout << "Health: " << player->getHealth()
                      << ", Damage: " << player->getDamage()
                      << ", Defense: " << player->getDefense() << "\n";

            ++roomIndex; // Move to the next room after exploring

        } else if (choice == 2) {
            std::cout << "You skipped this room.\n";
            ++roomIndex; // Move to the next room after skipping

        } else if (choice == 3) {
            // Resting logic: Heal a fixed amount or based on player's class
            int healAmount = 15;
            player->setHealth(player->getHealth() + healAmount);
            std::cout << "You take a moment to rest and regain " << healAmount << " health.\n";
            std::cout << "Your current health: " << player->getHealth() << "\n";

            // Do not increment `roomIndex`, so the player stays in the same room
        } else {
            std::cout << "Invalid choice. You stay in the room and rest.\n";
        }
    }

    if (player->isAlive()) {
        std::cout << "\nCongratulations! You have defeated the Dragon and completed the dungeon.\n";
        std::cout << "Final Player Stats:\n";
        std::cout << "Health: " << player->getHealth()
                  << ", Damage: " << player->getDamage()
                  << ", Defense: " << player->getDefense() << "\n";
    }

    std::cout << "\nThank you for playing! See you on your next adventure!\n";

    // Clean up
    delete player;
    return 0;
}
