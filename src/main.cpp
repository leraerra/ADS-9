// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include "tree.h"

int main() {
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::vector<std::vector<char>> all = getAllPerms(tree);
    for (size_t i = 0; i < all.size(); ++i) {
        for (size_t j = 0; j < all[i].size(); ++j) {
            std::cout << all[i][j];
        }
        std::cout << " ";
    }
    std::cout << "\n\n";

    int search_num = 4;
    std::vector<char> p1 = getPerm1(tree, search_num);
    for (char c : p1) std::cout << c;
    std::cout << "\n";

    std::vector<char> p2 = getPerm2(tree, search_num);
    for (char c : p2) std::cout << c;
    std::cout << "\n\n";

    std::vector<int> sizes = {3, 4, 5, 6, 7, 8};

    for (int n : sizes) {
        std::vector<char> test_in;
        for (int i = 0; i < n; ++i) {
            test_in.push_back('A' + i);
        }

        PMTree test_tree(test_in);

        int test_num = 1;
        for (int i = 1; i <= n; ++i) test_num *= i;
        test_num = test_num - 1;

        auto start1 = std::chrono::high_resolution_clock::now();
        getPerm1(test_tree, test_num);
        auto stop1 = std::chrono::high_resolution_clock::now();
        auto dur1 = std::chrono::duration_cast<std::chrono::nanoseconds>(
            stop1 - start1).count();

        auto start2 = std::chrono::high_resolution_clock::now();
        getPerm2(test_tree, test_num);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto dur2 = std::chrono::duration_cast<std::chrono::nanoseconds>(
            stop2 - start2).count();

        std::cout << "N = " << n << "\t|"
             << " getPerm1: " << dur1 << " ns \t|"
             << " getPerm2: " << dur2 << " ns\n";
    }

    return 0;
}
