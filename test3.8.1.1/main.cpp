#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std;

// ������� ��� ��������� ����� ������ �����
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// ������� ��� ���������� � ������������
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// ������� ��� ���������� ����������� �����
char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
}

// ������� ��� ������ ����� � ����������� �� �����
string selectGamma(int cycle) {
    switch (cycle) {
        case 1: return "ABCD EFGH IJKL MNOP";
        case 2: return "GHAB OPIJ MNCD KLEF";
        case 3: return "GHEF CDAB OPMN KLIJ";
        default: return "ABCD EFGH IJKL MNOP"; // ����������� ����� �� ������ ������
    }
}

// ����� ��� ������� generateKey
void testGenerateKey() {
    assert(generateKey("key", 10) == "keykeykeyk");
    assert(generateKey("abc", 5) == "abcab");
    assert(generateKey("12345", 10) == "1234512345");
    cout << "testGenerateKey �������" << endl;
}

// ����� ��� ������� xorCipher
void testXorCipher() {
    string data = "hello";
    string key = "keyke";
    string encrypted = xorCipher(data, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == data);
    cout << "testXorCipher �������" << endl;
}

// ����� ��� ������� calculateChecksum
void testCalculateChecksum() {
    assert(calculateChecksum("hello") == 'h' ^ 'e' ^ 'l' ^ 'l' ^ 'o');
    assert(calculateChecksum("test") == 't' ^ 'e' ^ 's' ^ 't');
    cout << "testCalculateChecksum �������" << endl;
}

// ����� ��� ������� selectGamma
void testSelectGamma() {
    assert(selectGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(selectGamma(2) == "GHAB OPIJ MNCD KLEF");
    assert(selectGamma(3) == "GHEF CDAB OPMN KLIJ");
    assert(selectGamma(4) == "ABCD EFGH IJKL MNOP"); // ����������� ����� �� ������ ������
    cout << "testSelectGamma �������" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    testGenerateKey();
    testXorCipher();
    testCalculateChecksum();
    testSelectGamma();
    cout << "��� ����� ��������!" << endl;
    return 0;
}
