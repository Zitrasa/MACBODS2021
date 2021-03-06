#include <fstream>
#include <utility>

#include "cipher.h"

/*
* Номер в списке: 19 => число для шифрования: 133
* Q = 6, R = 6 => Ключ: 3700
*/
constexpr uint8_t message = 0b10000101;
constexpr uint16_t key = 0b111001110100;

int main() {
    setlocale(LC_ALL, "Russian");
    std::ofstream out("Report.txt");

    /*
    * Создание объекта декодера.
    * Ему необходимо передать таблицы перестановок обеих S - блоков.
    */
    Cipher cipher(std::make_pair(
        SBlock({ 14, 7, 10, 12, 13, 1, 3, 9, 0, 2, 11, 4, 15, 8, 5, 6 }), 
        SBlock({ 3, 7, 14, 9, 8, 10, 15, 0, 5, 2, 6, 12, 11, 4, 13, 1 })));
    
    /*
    * Последовательное получение результатов на каждой итерации.
    */
    auto first_iteration = cipher.Iterate(message, key, { 9, 11, 1, 4, 7, 5, 8, 3 });
    auto second_iteration = cipher.Iterate(first_iteration, key, { 1, 8, 9, 4, 0, 11, 5, 3 });
    auto third_iteration = cipher.Iterate(second_iteration, key, { 6, 0, 1, 5, 11, 2, 8, 10 });

    /*
    * Далее только вывод и аналогичные операции для вывода результатов
    * для числа с измененным битом.
    */
    out << "Число для шифрования:\t\t" << std::bitset<8>(message) << std::endl;
    out << "Исходный ключ:\t\t\t" << std::bitset<12>(key) << std::endl;

    out << "Результат первой итерации:\t" << first_iteration << std::endl;
    out << "Результат второй итерации:\t" << second_iteration << std::endl;
    out << "Результат третьей итерации:\t" << third_iteration << std::endl;

    constexpr uint8_t twisted_message = 0b10010101;
    first_iteration = cipher.Iterate(twisted_message, key, { 9, 11, 1, 4, 7, 5, 8, 3 });
    second_iteration = cipher.Iterate(first_iteration, key, { 1, 8, 9, 4, 0, 11, 5, 3 });
    third_iteration = cipher.Iterate(second_iteration, key, { 6, 0, 1, 5, 11, 2, 8, 10 });

    out << "----------------------------------------------------------" << std::endl;
    out << "Новое число для шифрования:\t" << std::bitset<8>(twisted_message) << std::endl;
    out << "Исходный ключ:\t\t\t" << std::bitset<12>(key) << std::endl;

    out << "Результат первой итерации:\t" << first_iteration << std::endl;
    out << "Результат второй итерации:\t" << second_iteration << std::endl;
    out << "Результат третьей итерации:\t" << third_iteration << std::endl;

    return 0;
}