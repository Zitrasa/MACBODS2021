#pragma once

#include <stdexcept>
#include <bitset>
#include <vector>

struct SBlock {
    explicit SBlock(const std::initializer_list<size_t>& permutation);

    std::bitset<4> Convert(const std::bitset<4>& raw);

private:
    std::vector<size_t> permutation_;
};