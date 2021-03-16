#pragma once

#include <memory>
#include <vector>

#include "lsfr_generator.h"

class GeffeGenerator {
public:
    GeffeGenerator(LSFRGenerator* first_generator, LSFRGenerator* second_generator, 
        LSFRGenerator* third_generator) {
        generators_.emplace_back(first_generator);
        generators_.emplace_back(second_generator);
        generators_.emplace_back(third_generator);
    }
    
    bool Generate() {
        std::vector<bool> result;

        for (auto& generator : generators_) {
            result.push_back(generator->Generate());
        }
        
        return (result[0] & result[1]) ^ ((result[0] ^ 1) & result[2]);
    }

private:

    std::vector<std::unique_ptr<LSFRGenerator>> generators_;
};