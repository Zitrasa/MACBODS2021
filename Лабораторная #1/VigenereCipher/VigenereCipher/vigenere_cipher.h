#pragma once

#include <string>
#include <stdexcept>
#include <unordered_map>

class VigenereCipher {
public:

    VigenereCipher() = delete;

    explicit VigenereCipher(const std::u32string& alphabet) 
        : alphabet_(alphabet), alpha_codes_(GenerateAlphaCodes()) {
    }

    explicit VigenereCipher(const char32_t* alphabet) 
        : alphabet_(alphabet), alpha_codes_(GenerateAlphaCodes()) {
    }

    std::u32string Encrypt(const std::u32string& text, const std::u32string& key);

    std::u32string Decrypt(const std::u32string& text, const std::u32string& key);

private:

    std::u32string alphabet_;
    std::unordered_map<char32_t, uint32_t> alpha_codes_;

    std::unordered_map<char32_t, uint32_t> GenerateAlphaCodes();

    std::u32string GenerateExtendedKey(const std::u32string& key, const size_t length);
};