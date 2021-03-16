#pragma once

#include "lsfr_generator.h"

template <size_t S>
class LSFRGalois: public LSFRGenerator {
public:
    LSFRGalois(const std::bitset<S>& polynom, const std::bitset<S>& init) 
        : register_(init), reversed_polynom_(ReverseBitset(polynom)) {
    }

    virtual bool Generate() {
        if (register_[0]) {
            register_ = (register_ ^ reversed_polynom_) >> 1;
            register_[S - 1] = 1;

            return true;
        } else {
            register_ >>= 1;

            return false;
        }
    }

private:
    std::bitset<S> ReverseBitset(const std::bitset<S>& bitset) {
        std::bitset<S> reversed_bitset(bitset);

        for (size_t i = 0; i < S / 2; ++i) {
            bool bit = reversed_bitset[i];
            reversed_bitset[i] = reversed_bitset[S - i - 1];
            reversed_bitset[S - i - 1] = bit;
        }

        return reversed_bitset;
    }


    std::bitset<S> register_;
    std::bitset<S> reversed_polynom_;
};