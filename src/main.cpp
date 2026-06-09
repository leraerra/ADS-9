// Copyright 2022 NNTU-CS

#include <iostream>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};

  PMTree tree(in);

  std::vector<std::vector<char» perms = getAllPerms(tree);

  for (size_t i = 0; i < perms.size(); ++i) {
    for (size_t j = 0; j < perms[i].size(); ++j) {
      std::cout « perms[i][j];
    }
    std::cout « std::endl;
  }

  std::cout « std::endl;

  std::vector<char> p1 = getPerm1(tree, 1);

  for (size_t i = 0; i < p1.size(); ++i) {
    std::cout « p1[i];
  }

  std::cout « std::endl;

  std::vector<char> p2 = getPerm2(tree, 2);

  for (size_t i = 0; i < p2.size(); ++i) {
    std::cout « p2[i];
  }

  std::cout « std::endl;

  return 0;
}
