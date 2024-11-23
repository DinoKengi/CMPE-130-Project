#include "Story.h"
#include <iostream>

// Constructor for StoryNode
StoryNode::StoryNode(const std::string& desc)
    : description(desc), left(nullptr), right(nullptr) {}

// Constructor for Story
Story::Story()
    : root(nullptr) {}

// Destructor for Story
Story::~Story() {
    deleteTree(root);
}

// Add a node to the story
void Story::addNode(const std::string& desc, StoryNode* left, StoryNode* right) {
    if (!root) {
        root = new StoryNode(desc); // Create root if it doesn't exist
        root->left = left;
        root->right = right;
    } else {
        std::cerr << "Warning: Root already exists. Add nodes manually to left or right.\n";
    }
}

// Display story based on player's decisions
void Story::displayStory(StoryNode* node) {
    if (!node) return;

    std::cout << node->description << "\n";

    // Check if the node has children
    if (node->left || node->right) {
        std::cout << "1) " << (node->left ? node->left->description : "No choice available") << "\n";
        std::cout << "2) " << (node->right ? node->right->description : "No choice available") << "\n";

        int choice;
        do {
            std::cout << "Enter your choice (1 or 2): ";
            std::cin >> choice;
        } while (choice != 1 && choice != 2);

        if (choice == 1 && node->left) {
            displayStory(node->left); // Traverse left
        } else if (choice == 2 && node->right) {
            displayStory(node->right); // Traverse right
        }
    }
}

// Get the root node for traversal
StoryNode* Story::getRoot() {
    return root;
}

// Delete the entire tree
void Story::deleteTree(StoryNode* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}
