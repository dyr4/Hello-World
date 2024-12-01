#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std;

// Функция для генерации ключа нужной длины
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

// Функция для вычисления контрольной суммы
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// Функция для выбора гаммы в зависимости от цикла
string selectGamma(int cycle) {
    switch (cycle) {
        case 1: return "ABCD EFGH IJKL MNOP";
        case 2: return "GHAB OPIJ MNCD KLEF";
        case 3: return "GHEF CDAB OPMN KLIJ";
        default: return "ABCD EFGH IJKL MNOP"; // Стандартная гамма на случай ошибки
    }
}

// Тесты для функции generateKey
void testGenerateKey() {
    assert(generateKey("key", 10) == "keykeykeyk");
    assert(generateKey("abc", 5) == "abcab");
    assert(generateKey("12345", 10) == "1234512345");
    cout << "testGenerateKey пройден" << endl;
}

// Тесты для функции xorCipher
void testXorCipher() {
    string data = "hello";
    string key = "keyke";
    string encrypted = xorCipher(data, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == data);
    cout << "testXorCipher пройден" << endl;
}

// Тесты для функции calculateChecksum
void testCalculateChecksum() {
    assert(calculateChecksum("hello") == 'h' ^ 'e' ^ 'l' ^ 'l' ^ 'o');
    assert(calculateChecksum("test") == 't' ^ 'e' ^ 's' ^ 't');
    cout << "testCalculateChecksum пройден" << endl;
}

// Тесты для функции selectGamma
void testSelectGamma() {
    assert(selectGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(selectGamma(2) == "GHAB OPIJ MNCD KLEF");
    assert(selectGamma(3) == "GHEF CDAB OPMN KLIJ");
    assert(selectGamma(4) == "ABCD EFGH IJKL MNOP"); // Стандартная гамма на случай ошибки
    cout << "testSelectGamma пройден" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    testGenerateKey();
    testXorCipher();
    testCalculateChecksum();
    testSelectGamma();
    cout << "Все тесты пройдены!" << endl;
    return 0;
}
