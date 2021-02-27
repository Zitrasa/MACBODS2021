#pragma once

#include <string>
#include <random>
#include <codecvt>
#include <fstream>
#include <unordered_map>

/*
* ����� � ����� �����������, ������� ������� � ����� ���������, �� ������ ���,
* ��� ������� ����� ����������������.
* 
* > kPenalty:        ����� �� ���������� ������ ������������ ���������� � ������
* > KIterationCount: ���������� �������� ������������ ���� � �����
* > kSeed:           ����� ��������� ��������� ������������   
*/

#define kPenalty 0
#define kIterationCount 8000
#define kSeed 28975

// ���������� ����������� ��������� ������� �������, � ���������
const std::u32string alphabet = U"�����Ũ�������������������������� ";

using Map = std::unordered_map<std::u32string, double>;


// ������� ��� ������� ����������� UTF8 <-> UTF32
std::u32string UTF8To32(const std::string& utf8) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
    return convert.from_bytes(utf8);
}

std::string UTF32To8(const std::u32string& utf32) {
    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> cvt;
    return cvt.to_bytes(utf32);
}


/* 
* ������� ��� ������ UTF8 ������ � ���������� ��� � UTF32, 
* ��� �� ����� �� ������� ������ � �������������� ���������.
*/ 
inline std::u32string ReadFile(const std::string& filename) {
    std::ifstream fin(filename);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    fin.imbue(loc);

    std::u32string text;

    while (!fin.eof()) {
        std::string line;
        std::getline(fin, line);

        text += UTF8To32(line);
    }

    return text;
}

/*
* ��� ������� ������ ���������. � ���� ������� � ��������� 
* ������������� ������� ������� � ������� ����� ��������� ����.
* 
* � �� �� �����, ������ ����� ��������������� �������, ����� ��������
* ������� � ������� ��������.
*/
inline Map ReadNgrams(const std::string& filename) {
    std::unordered_map<std::u32string, double> map;
    std::ifstream fin(filename);
    std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
    fin.imbue(loc);

    std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;

    while (!fin.eof()) {
        std::string key;
        double value;

        fin >> key >> value;
        map[convert.from_bytes(key)] = log(value);
    }

    fin.close();
    return map;
}

/*
* ��� ������� �������� ���������. � ��� ���������� ��� ����:
*   1. ��������� ������� � ����� �������� ������� ��� �����.
*   2. ������������ ����� ����� ��������, ������� ���������� ��� ����������� ����� ������.
*/
std::u32string Iteration(const std::u32string& capital_text, std::mt19937* gen) {
    std::uniform_int_distribution<int> distribution(0, 33);

    char32_t swap_first = alphabet[distribution(*gen)];
    char32_t swap_second = alphabet[distribution(*gen)];

    std::u32string new_text;

    for (auto symbol : capital_text) {
        if (symbol == swap_first) {
            new_text.push_back(swap_second);
        } else if (symbol == swap_second) {
            new_text.push_back(swap_first);
        } else {
            new_text.push_back(symbol);
        }
    }

    return new_text;
}

/*
* ���� ���� ������� - ������� �������������� ���� �������� ������ �� ������� �����.
* ��� ����� ��� ������� �������� ������� ����������� ���� ������� ����� � �������� ��������.
*/
double MeasureFitness(const std::u32string& text, const Map& dict) {
    double fitness = 0;

    for (size_t i = 0; i < text.length() - 4; i++) {
        std::u32string substring = text.substr(i, 4);

        if (dict.find(substring) == dict.end()) {
            fitness += kPenalty;
        } else {
            fitness += dict.at(substring);
        }
    }

    return fitness;
}

/*
* ������� ������� ���������. 
* ������� ������: �������� ����������� ���������� ������ ��������.
*/
inline std::u32string Decode(const std::u32string& text, const Map& dict) {
    std::mt19937 gen(kSeed);
    std::u32string capital_text = text;

    for (int i = 0; i < kIterationCount; i++) {
        std::u32string new_text = Iteration(capital_text, &gen);
        if (MeasureFitness(capital_text, dict) < MeasureFitness(new_text, dict)) {
            capital_text = new_text;
        }
    }

    return capital_text;
}

int main() {
    std::u32string text = ReadFile("text.txt");

    std::ofstream out("Report.txt", std::ofstream::binary);

    out << UTF32To8(Decode(text, ReadNgrams("russian_quadgrams.txt")));

    out.close();

    return 0;
}
