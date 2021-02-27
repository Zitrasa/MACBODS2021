#include "substitution_cipher.h"

std::unordered_map<char32_t, char32_t> SubstitutionCipher::GenerateSubstitutionMap(const std::u32string &key,
                                                                                 CipherType type) {
    if (alphabet_.size() != key.size()) {
        throw std::length_error("Invalid key or alphabet passed.");
    }

    std::unordered_map<char32_t, char32_t> symbol_map;
    std::u32string from_set = (type == CipherType::kEncrypt ? alphabet_ : key);
    std::u32string to_set = (type == CipherType::kEncrypt ? key : alphabet_);

    for (size_t index = 0; index < from_set.length(); ++index) {
        symbol_map[from_set[index]] = to_set[index];
    }

    return symbol_map;
}

std::u32string SubstitutionCipher::MakeSubstitution(const std::u32string &text,
                                                  std::unordered_map<char32_t, char32_t> &symbol_map) {
    std::u32string result;
    for (auto symbol: text) {
        if (!symbol_map.count(symbol)) {
            throw std::invalid_argument("Text contain non-alphabet symbols.");
        }

        result.push_back(symbol_map[symbol]);
    }

    return result;
}

std::u32string SubstitutionCipher::Encrypt(const std::u32string &text, const std::u32string &key) {
    std::unordered_map<char32_t, char32_t> symbol_map = GenerateSubstitutionMap(key, CipherType::kEncrypt);
    return MakeSubstitution(text, symbol_map);
}

std::u32string SubstitutionCipher::Decrypt(const std::u32string &text, const std::u32string &key) {
    std::unordered_map<char32_t, char32_t> symbol_map = GenerateSubstitutionMap(key, CipherType::kDecrypt);
    return MakeSubstitution(text, symbol_map);
}
