// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

class PMTree {
public:
    struct Node {
        char sym;
        std::vector<Node*> links;
    };
    explicit PMTree(const std::vector<char>& src);
    ~PMTree();

private:
    Node* root;
    Node* generate(const std::vector<char>& available);
    void destroy(Node* nodePtr);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
size_t fact(int n);

#endif // INCLUDE_TREE_H_
