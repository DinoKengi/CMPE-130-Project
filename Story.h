#ifndef STORY_H
#define STORY_H

#include <string>

class StoryNode {
public:
    std::string description;  // description of the current story point
    StoryNode* left;          // left choice (binary decision)
    StoryNode* right;         // right choice (binary decision)

    StoryNode(const std::string& desc);
};

class Story {
public:
    Story();
    ~Story();
    
    void addNode(const std::string& desc, StoryNode* left = nullptr, StoryNode* right = nullptr);
    void displayStory(StoryNode* node);  // displays story based on player’s decisions
    StoryNode* getRoot();                // get root node for traversal

private:
    StoryNode* root;
    void deleteTree(StoryNode* node);    // utility to delete the tree, resets after each run
};

#endif
