#include "../include/permutations.h"
#include <algorithm>


void Permutations::backtrack(int start, int n, std::vector<uint8_t>& current, std::vector<std::vector<uint8_t>>& res){
    if(start == n){
        res.push_back(current);
        return;
    }

    for(int i = start; i < n; ++i){
        std::swap(current[start], current[i]);
        backtrack(start + 1, n, current, res);
        std::swap(current[start], current[i]); // backtrack
    }
}

// returns the shortest order preserving vector containing s1 and s2
std::vector<uint8_t> Permutations::reduce(const std::vector<uint8_t>& s1, const std::vector<uint8_t>& s2){
    // checks if one sequence contains another
    if (std::search(s1.begin(), s1.end(), s2.begin(), s2.end()) != s1.end()) return s1;
    if (std::search(s2.begin(), s2.end(), s1.begin(), s1.end()) != s2.end()) return s2;

    int overlap12 = getOverlap(s1, s2);
    int overlap21 = getOverlap(s2, s1);

    if(overlap12 >= overlap21){
        std::vector<uint8_t> res = s1;
        res.insert(res.end(), s2.begin() + overlap12, s2.end());
        return res;
    } else{
        std::vector<uint8_t> res = s2;
        res.insert(res.end(), s1.begin() + overlap21, s1.end());
        return res;
    }
}

int Permutations::getOverlap(const std::vector<uint8_t>& s1, const std::vector<uint8_t>& s2){
    int maxPossible = std::min(s1.size(), s2.size());

    for(int len = maxPossible; len > 0; --len){
        if(std::equal(s1.end() - len, s1.end(), s2.begin())){
            return len;
        }
    }

    return 0;
}

std::vector<std::vector<uint8_t>> Permutations::getPermutations(int n) {
    std::vector<std::vector<uint8_t>> res;

    int total = 1;
    for (int i = 2; i <= n; ++i) total *= i;
    res.reserve(total);

    std::vector<uint8_t> current(n);
    for (int i = 0; i < n; ++i) current[i] = i + 1;

    backtrack(0, n, current, res);

    return res;
}

std::vector<uint8_t> Permutations::getSuperpermutation(std::vector<std::vector<uint8_t>> perms) {
    if (perms.empty()) return {};

    std::vector<uint8_t> result = perms[0];
    std::vector<bool> used(perms.size(), false);
    used[0] = true;

    for (size_t count = 1; count < perms.size(); ++count) {
        int bestOverlap = -1;
        int bestIdx = -1;

        for (size_t j = 0; j < perms.size(); ++j) {
            if (used[j]) continue;

            // Use the overlap logic we built earlier
            int overlap = getOverlap(result, perms[j]);
            if (overlap > bestOverlap) {
                bestOverlap = overlap;
                bestIdx = j;
            }
        }

        // Append the unique part of the best match
        result.insert(result.end(), perms[bestIdx].begin() + bestOverlap, perms[bestIdx].end());
        used[bestIdx] = true;
    }
    return result;
}


bool Permutations::isSuperpermutation(const std::vector<std::vector<uint8_t>>& perms, const std::vector<uint8_t>& superpermutation){
    for(const auto& p : perms){
        auto it = std::search(superpermutation.begin(), superpermutation.end(), p.begin(), p.end());

        if(it == superpermutation.end()){
            return false;
        }
    }

    return true;
}
