#include <iostream>
#include <cassert>
#include <string>

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

// Юнит-тесты
void testGenerateKey() {
    assert(generateKey("key", 10) == "keykeykeyk");
    assert(generateKey("abc", 5) == "abcab");
    assert(generateKey("x", 3) == "xxx");
    cout << "testGenerateKey passed" << endl;
}

void testXorCipher() {
    string data = "hello";
    string key = "world";
    string encrypted = xorCipher(data, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == data);
    cout << "testXorCipher passed" << endl;
}

void testCalculateChecksum() {
    assert(calculateChecksum("hello") == 'h' ^ 'e' ^ 'l' ^ 'l' ^ 'o');
    assert(calculateChecksum("world") == 'w' ^ 'o' ^ 'r' ^ 'l' ^ 'd');
    cout << "testCalculateChecksum passed" << endl;
}

void testSelectGamma() {
    assert(selectGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(selectGamma(2) == "GHAB OPIJ MNCD KLEF");
    assert(selectGamma(3) == "GHEF CDAB OPMN KLIJ");
    assert(selectGamma(0) == "ABCD EFGH IJKL MNOP"); // Стандартная гамма на случай ошибки
    cout << "testSelectGamma passed" << endl;
}

int main() {
    testGenerateKey();
    testXorCipher();
    testCalculateChecksum();
    testSelectGamma();
    cout << "All tests passed!!" << endl;
    return 0;
}
