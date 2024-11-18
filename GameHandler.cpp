#include "GameHandler.h"
#include <iostream>
using namespace std;

GameManager::GameManager(int numRooms) : exploration(numRooms) {}

void GameManager::startGame() {
    std::cout << "Welcome to the game!" << std::endl;
    explore();
}

void GameManager::explore() {
    std::cout << "Choose your map generation algorithm:\n";
    std::cout << "1. Prim's Algorithm\n";
    std::cout << "2. Kruskal's Algorithm\n";

    int choice;
    std::cin >> choice;

    bool useKruskal = (choice == 2);
    exploration.genTree(useKruskal);

    std::cout << "Exploration setup complete. Begin your journey!" << std::endl;
}
