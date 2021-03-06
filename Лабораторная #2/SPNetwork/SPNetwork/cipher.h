#pragma once

#include <utility>
#include <bitset>

#include "p_block.h"
#include "s_block.h"

class Cipher {
public:
    Cipher(const std::pair<SBlock, SBlock>& sblocks);

    std::bitset<8> Iterate(const std::bitset<8>& data, const std::bitset<12>& key,
        const std::vector<size_t>& round_permutation);

private:
    std::bitset<8> GenerateRoundKey(const std::bitset<12>& key, 
        const std::vector<size_t> round_permutation);

    std::pair<std::bitset<4>, std::bitset<4>> Split(const std::bitset<8>& bits);

    std::bitset<8> Concatenate(const std::bitset<4>& left_part,
        const std::bitset<4>& right_part);

    std::pair<SBlock, SBlock> sblocks_;
};

