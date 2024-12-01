#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cassert>

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// Функция для вычисления контрольной суммы на основе исходного текста
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// Функция для получения текущего дня
int getDay() {
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));
    cout << "Текущая дата: " << buf << endl;
    return stoi(buf);
}

// Тесты
void testGenerateKey() {
    string key = "ABC";
    string expected = "ABCABCABC";
    string result = generateKey(key, 9);
    assert(result == expected);
}

void testXorCipher() {
    string data = "Hello";
    string key = "ABCDE";
    string encrypted = xorCipher(data, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == data);
}

void testCalculateChecksum() {
    string data = "Hello";
    char checksum = calculateChecksum(data);
    char expected = 'H' ^ 'e' ^ 'l' ^ 'l' ^ 'o';
    assert(checksum == expected);
}

void testGetDay() {
    int day = getDay();
    assert(day >= 1 && day <= 31);
}

int main() {
    setlocale(LC_ALL, "Russian");
    testGenerateKey();
    testXorCipher();
    testCalculateChecksum();
    testGetDay();

    cout << "Все тесты пройдены успешно!" << endl;
    return 0;
}
