#include "p_block.h"

std::bitset<8> PBlock::Convert(const std::bitset<8>& raw) {
    return raw << 3 | raw >> 5;
}
