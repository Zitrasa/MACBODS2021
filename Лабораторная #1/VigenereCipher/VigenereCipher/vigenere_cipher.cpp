#include "vigenere_cipher.h"

std::u32string VigenereCipher::Encrypt(const std::u32string& text, const std::u32string& key) {
    size_t alpha_size = alphabet_.size();

    std::u32string extended_key = GenerateExtendedKey(key, text.size());
    std::u32string encoded_text;
    encoded_text.resize(text.size());

    for (size_t index = 0; index < text.size(); ++index) {
        if (!alpha_codes_.count(text[index]) || !alpha_codes_.count(extended_key[index])) {
            throw std::invalid_argument("Key or text symbol not in the alphabet.");
        }

        auto code = (alpha_codes_[text[index]] + alpha_codes_[extended_key[index]]) % alpha_size;
        encoded_text[index] = alphabet_[code];
    }

    return encoded_text;
}

std::u32string VigenereCipher::Decrypt(const std::u32string& text, const std::u32string& key) {
    size_t alpha_size = alphabet_.size();

    std::u32string extended_key = GenerateExtendedKey(key, text.size());
    std::u32string decoded_text;
    decoded_text.resize(text.size());

    for (size_t index = 0; index < text.size(); ++index) {
        if (!alpha_codes_.count(text[index]) || !alpha_codes_.count(extended_key[index])) {
            throw std::invalid_argument("Key or text symbol not in the alphabet.");
        }

        size_t code =
            (alpha_codes_[text[index]] + alpha_size - alpha_codes_[extended_key[index]])
            % alpha_size;

        decoded_text[index] = alphabet_[code];
    }

    return decoded_text;
}

std::unordered_map<char32_t, uint32_t> VigenereCipher::GenerateAlphaCodes() {
    uint32_t code = 0;
    std::unordered_map<char32_t, uint32_t> alpha_codes;

    for (auto symbol : alphabet_) {
        alpha_codes[symbol] = code++;
    }

    return alpha_codes;
}

std::u32string VigenereCipher::GenerateExtendedKey(const std::u32string& key, const size_t length) {
    std::u32string extended_key;
    extended_key.resize(length);

    for (size_t index = 0; index < length; ++index) {
        extended_key[index] = key[index % key.size()];
    }

    return extended_key;
}