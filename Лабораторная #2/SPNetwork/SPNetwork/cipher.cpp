#include "cipher.h"

Cipher::Cipher(const std::pair<SBlock, SBlock>& sblocks) : sblocks_(sblocks) {
}

std::bitset<8> Cipher::Iterate(const std::bitset<8>& data, const std::bitset<12>& key,
    const std::vector<size_t>& round_permutation) {
    auto round_key = GenerateRoundKey(key, round_permutation);
    auto parts = Split(data ^ round_key);

    auto left_processed = sblocks_.first.Convert(parts.first);
    auto right_processed = sblocks_.second.Convert(parts.second);

    return PBlock::Convert(Concatenate(left_processed, right_processed));
}

std::bitset<8> Cipher::GenerateRoundKey(const std::bitset<12>& key,
    const std::vector<size_t> round_permutation) {
    std::bitset<8> round_key;

    for (size_t bit_index = 0; bit_index < 8; ++bit_index) {
        round_key[7 - bit_index] = key[11 - round_permutation[bit_index]];
    }

    return round_key;
}

std::pair<std::bitset<4>, std::bitset<4>> Cipher::Split(const std::bitset<8>& bits) {
    std::bitset<4> left_part, right_part;

    for (size_t i = 0; i < 4; ++i) {
        left_part[i] = bits[i + 4];
        right_part[i] = bits[i];
    }

    return std::make_pair(left_part, right_part);
}

std::bitset<8> Cipher::Concatenate(const std::bitset<4>& left_part,
    const std::bitset<4>& right_part) {
    std::bitset<8> concatenated;

    for (size_t i = 0; i < 4; ++i) {
        concatenated[i + 4] = left_part[i];
        concatenated[i] = right_part[i];
    }

    return concatenated;
}