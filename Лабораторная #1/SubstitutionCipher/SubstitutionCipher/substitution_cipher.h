#include <string>
#include <stdexcept>
#include <unordered_map>

class SubstitutionCipher {
public:
    SubstitutionCipher() = delete;

    explicit SubstitutionCipher(const std::u32string &alphabet) : alphabet_(alphabet) {
    }

    explicit SubstitutionCipher(const char32_t *alphabet) : alphabet_(alphabet) {
    }

    std::u32string Encrypt(const std::u32string &text, const std::u32string &key);

    std::u32string Decrypt(const std::u32string &text, const std::u32string &key);

private:
    std::u32string alphabet_;

    enum class CipherType {
        kEncrypt,
        kDecrypt
    };

    std::unordered_map<char32_t, char32_t> GenerateSubstitutionMap(const std::u32string &key, CipherType type);

    static std::u32string MakeSubstitution(const std::u32string &text,
                                           std::unordered_map<char32_t, char32_t> &symbol_map);
};
