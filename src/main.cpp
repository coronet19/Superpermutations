#include <iostream>
#include <vector>
#include <string>
#include "../include/permutations.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./superpermutation <n>" << std::endl;
        return 1;
    }

    int n = std::stoi(argv[1]);
    if(n < 1){
        std::cout << "Enter a positive number" << std::endl;
        return 1;
    }

    for(int i = 1; i <= n; ++i){
        std::vector<std::vector<uint8_t>> perms = Permutations::getPermutations(i);
        std::vector<uint8_t> super = Permutations::getSuperpermutation(perms);

        assert(Permutations::isSuperpermutation(perms, super)); // verification is always good

        std::string out = "";
        out.reserve(super.size() * 4); // probably not optimal. string uses 4 bytes per character, uint8_t is 1 byte. so maybe it is? idk
        for(const auto& val : super){
            out += std::to_string((int)val);
        }

        // printf("n: %d, size: %zu, string: %s\n", i, super.size(), out.c_str());
        printf("n: %d, size: %zu\n", i, super.size());
    }

    return 0;
}
