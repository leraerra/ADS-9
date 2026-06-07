// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

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
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n : sizes) {
        std::vector<char> test_in;
        for (int i = 0; i < n; ++i) {
            test_in.push_back('A' + i);
        }

        PMTree test_tree(test_in);

        size_t max_perms = fact(n);
        std::uniform_int_distribution<> dist(1, max_perms);
        int test_num = dist(gen);

        auto start1 = std::chrono::high_resolution_clock::now();
        getPerm1(test_tree, test_num);
        auto stop1 = std::chrono::high_resolution_clock::now();
        auto dur1 = std::chrono::duration_cast<std::chrono::microseconds>(stop1 - start1).count();

        auto start2 = std::chrono::high_resolution_clock::now();
        getPerm2(test_tree, test_num);
        auto stop2 = std::chrono::high_resolution_clock::now();
        auto dur2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2).count();

        std::cout << "N = " << n << "\t| getPerm1: " << dur1 << " mks \t| getPerm2: " << dur2 << " mks\n";
    }

    return 0;
}
