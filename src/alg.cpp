// Copyright 2022 NNTU-CS

#include <algorithm>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& src) {
  root = new Node();
  root->sym = '\0';

  std::vector<char> sorted = src;
  std::sort(sorted.begin(), sorted.end());

  for (size_t i = 0; i < sorted.size(); ++i) {
    Node* child = new Node();
    child->sym = sorted[i];

    std::vector<char> rest;
    for (size_t j = 0; j < sorted.size(); ++j) {
      if (i != j) {
        rest.push_back(sorted[j]);
      }
    }

    Node* subtree = generate(rest);

    if (subtree != nullptr) {
      child->links = subtree->links;
      delete subtree;
    }

    root->links.push_back(child);
  }
}

PMTree::~PMTree() {
  destroy(root);
}

PMTree::Node* PMTree::generate(const std::vector<char>& available) {
  Node* node = new Node();
  node->sym = '\0';

  for (size_t i = 0; i < available.size(); ++i) {
    Node* child = new Node();
    child->sym = available[i];

    std::vector<char> rest;

    for (size_t j = 0; j < available.size(); ++j) {
      if (i != j) {
        rest.push_back(available[j]);
      }
    }

    if (!rest.empty()) {
      Node* subtree = generate(rest);

      child->links = subtree->links;

      delete subtree;
    }

    node->links.push_back(child);
  }

  return node;
}

void PMTree::destroy(Node* nodePtr) {
  if (nodePtr == nullptr) {
    return;
  }

  for (size_t i = 0; i < nodePtr->links.size(); ++i) {
    destroy(nodePtr->links[i]);
  }

  delete nodePtr;
}

size_t fact(int n) {
  size_t result = 1;

  for (int i = 2; i <= n; ++i) {
    result *= i;
  }

  return result;
}

void dfsAll(PMTree::Node* node,
            std::vector<char>* path,
            std::vector<std::vector<char»* result) {
  path->push_back(node->sym);

  if (node->links.empty()) {
    result->push_back(*path);
    path->pop_back();
    return;
  }

  for (size_t i = 0; i < node->links.size(); ++i) {
    dfsAll(node->links[i], path, result);
  }

  path->pop_back();
}

std::vector<std::vector<char» getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char» result;

  if (tree.root == nullptr) {
    return result;
  }

  std::vector<char> path;

  for (size_t i = 0; i < tree.root->links.size(); ++i) {
    dfsAll(tree.root->links[i], &path, &result);
  }

  return result;
}

void dfsPerm(PMTree::Node* node,
             std::vector<char>* path,
             int target,
             int* counter,
             std::vector<char>* answer) {
  if (!answer->empty()) {
    return;
  }

  path->push_back(node->sym);

  if (node->links.empty()) {
    ++(*counter);

    if (*counter == target) {
      @id856347212 (*answer) = *path;
    }

    path->pop_back();
    return;
  }

  for (size_t i = 0; i < node->links.size(); ++i) {
    dfsPerm(node->links[i], path, target, counter, answer);
  }

  path->pop_back();
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  std::vector<char> answer;

  if (tree.root == nullptr || num < 1) {
    return answer;
  }

  int counter = 0;
  std::vector<char> path;

  for (size_t i = 0; i < tree.root->links.size(); ++i) {
    dfsPerm(tree.root->links[i],
            &path,
            num,
            &counter,
            &answer);

    if (!answer.empty()) {
      break;
    }
  }

  return answer;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  std::vector<char> perms = getPerm1(tree, num);
  return perms;
}
