#include "s_block.h"

SBlock::SBlock(const std::initializer_list<size_t>& permutation) : permutation_(permutation) {
    if (permutation_.size() < 16) {
        throw std::invalid_argument("Invalid permutation size.");
    }
}

std::bitset<4> SBlock::Convert(const std::bitset<4>& raw) {
    return std::bitset<4>(permutation_[raw.to_ulong()]);
}