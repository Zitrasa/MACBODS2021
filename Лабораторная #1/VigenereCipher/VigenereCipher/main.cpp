#pragma warning(disable : 4996)

#include <string>
#include <fstream>
#include <codecvt>

#include "vigenere_cipher.h"

const std::u32string russian_alphabet = U"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const std::u32string text = U"ЛИКШЙПЛ";
const std::u32string key = U"ЛБВ";

std::string UTF32ToUTF8(const std::u32string& utf32) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
    return cvt.to_bytes(utf32);
}

int main() {
    VigenereCipher cipher(russian_alphabet);
    
    std::ofstream out("Report.txt", std::ofstream::binary);

    auto decoded_text = cipher.Decrypt(text, key);
    auto encoded_text = cipher.Encrypt(decoded_text, key);

    out << "Ключ: " << UTF32ToUTF8(key) << std::endl;
    out << "Исходный (зашифрованный) текст: " << UTF32ToUTF8(text) << std::endl;
    out << "Расшифрованный текст: " << UTF32ToUTF8(decoded_text) << std::endl;
    out << "Зашифрованный текст: " << UTF32ToUTF8(encoded_text) << std::endl;

    out.close();

    return 0;
}