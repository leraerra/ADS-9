// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& src) {
    std::vector<char> sorted = src;
    std::sort(sorted.begin(), sorted.end());
    root = new Node();
    root->sym = '*';
    for (size_t i = 0; i < sorted.size(); ++i) {
        std::vector<char> remaining;
        for (size_t j = 0; j < sorted.size(); ++j) {
            if (j != i) remaining.push_back(sorted[j]);
        }
        Node* child = generate(remaining);
        child->sym = sorted[i];
        root->links.push_back(child);
    }
}

PMTree::~PMTree() {
    destroy(root);
}

PMTree::Node* PMTree::generate(const std::vector<char>& available) {
    if (available.empty()) return nullptr;
    Node* node = new Node();
    node->sym = available[0];
    if (available.size() > 1) {
        std::vector<char> remaining;
        for (size_t i = 1; i < available.size(); ++i) {
            remaining.push_back(available[i]);
        }
        node->links.push_back(generate(remaining));
    }
    return node;
}

void PMTree::destroy(Node* nodePtr) {
    if (!nodePtr) return;
    for (size_t i = 0; i < nodePtr->links.size(); ++i) {
        destroy(nodePtr->links[i]);
    }
    delete nodePtr;
}

void dfsAll(PMTree::Node* node, std::vector<char>& path,
            std::vector<std::vector<char>>& result) {
    path.push_back(node->sym);
    if (node->links.empty()) {
        result.push_back(path);
        path.pop_back();
        return;
    }
    for (size_t i = 0; i < node->links.size(); ++i) {
        dfsAll(node->links[i], path, result);
    }
    path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    if (!tree.root) return result;
    std::vector<char> path;
    for (size_t i = 0; i < tree.root->links.size(); ++i) {
        dfsAll(tree.root->links[i], path, result);
    }
    return result;
}

void dfs1(PMTree::Node* node, std::vector<char>& path, int target,
          int& count, std::vector<char>& result) {
    if (!result.empty()) return;
    path.push_back(node->sym);
    if (node->links.empty()) {
        count++;
        if (count == target) result = path;
        path.pop_back();
        return;
    }
    for (size_t i = 0; i < node->links.size(); ++i) {
        dfs1(node->links[i], path, target, count, result);
    }
    path.pop_back();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<char> result;
    if (!tree.root || num < 1) return result;
    int count = 0;
    std::vector<char> path;
    for (size_t i = 0; i < tree.root->links.size(); ++i) {
        dfs1(tree.root->links[i], path, num, count, result);
        if (!result.empty()) break;
    }
    return result;
}

size_t fact(int n) {
    size_t res = 1;
    for (int i = 2; i <= n; ++i) res *= i;
    return res;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> result;
    if (!tree.root || tree.root->links.empty()) return result;
    size_t total = fact(tree.root->links.size());
    if (num < 1 || num > (int)total) return result;
    int k = num - 1;
    PMTree::Node* current = tree.root;
    while (!current->links.empty()) {
        int L = current->links.size();
        int branch = fact(L - 1);
        int idx = k / branch;
        k = k % branch;
        current = current->links[idx];
        result.push_back(current->sym);
    }
    return result;
}
