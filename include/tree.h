// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
public:
    struct Node {
        char value;
        std::vector<Node*> children;
        Node(char val) : value(val) {}
    };

    explicit PMTree(std::vector<char> in);
    ~PMTree();

    Node* root;

private:
    void build(Node* current, std::vector<char> remaining);
    void destroy(Node* node);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
int getFact(int n);

#endif  // INCLUDE_TREE_H_
