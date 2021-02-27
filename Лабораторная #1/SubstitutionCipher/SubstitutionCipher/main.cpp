#pragma warning(disable : 4996)

#include <string>
#include <fstream>
#include <codecvt>

#include "substitution_cipher.h"

const std::u32string russian_alphabet = U"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const std::u32string text = U"КОНФИДЕНЦИАЛЬНОСТЬ";
const std::u32string key = U"ГЛФЫЗШБЖХЁПВЧНКЪЭДЬРЕТСАМЮЦЩЯУИОЙ";

std::string UTF32ToUTF8(const std::u32string& utf32) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
    return cvt.to_bytes(utf32);
}

int main() {
    SubstitutionCipher cipher(russian_alphabet);

    std::u32string encoded_text = cipher.Encrypt(text, key);
    std::u32string decoded_text = cipher.Decrypt(encoded_text, key);

    std::ofstream out("Report.txt", std::ofstream::binary);
    
    out << "Ключ: " << UTF32ToUTF8(key) << std::endl;
    out << "Открытый текст: " << UTF32ToUTF8(text) << std::endl;
    out << "Шифрованный текст: " << UTF32ToUTF8(encoded_text) << std::endl;
    out << "Расшифрованный текст: " << UTF32ToUTF8(decoded_text) << std::endl;

    out.close();

    return 0;
}