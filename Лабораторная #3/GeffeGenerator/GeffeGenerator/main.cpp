#include <iostream>
#include <fstream>
#include <memory>
#include <bitset>
#include <string>

#include "lsfr_galois.h"
#include "geffe_generator.h"

int main(int argc, char* argv[]) {
   
    if (argc < 2) {
        std::cout << "Invalid input format. You should specify bit-count to generate" << std::endl;
        return 0;
    }

    size_t generate_count = std::stoul(std::string(argv[1]));

    if (generate_count % 8) {
        std::cout << "Invalid input format. Bit-count should be multiply of 8" << std::endl;
        return 0;
    }

    GeffeGenerator generator({
        new LSFRGalois<23>(0x400019, 0x63d7e0), 
        new LSFRGalois<29>(0x10000046, 0x10bd2965), 
        new LSFRGalois<31>(0x4000001a, 0x7870d5b8) });

    std::ofstream out("Sequence.bin", std::ios::binary);

    for (size_t i = 0; i < generate_count; i += 8) {
        uint8_t current_byte = 0;
        for (int j = 7; j >= 0; --j) {
            current_byte |= static_cast<uint8_t>(generator.Generate()) << j;
        }

        out.write(reinterpret_cast<const char*>(&current_byte), sizeof(current_byte));
    }

    out.close();

    return 0;
}