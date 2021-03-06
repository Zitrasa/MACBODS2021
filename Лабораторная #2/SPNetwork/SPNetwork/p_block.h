#pragma once

#include <stdexcept>
#include <bitset>
#include <vector>

struct PBlock {
    static std::bitset<8> Convert(const std::bitset<8>& raw);
};