#include <iostream>
#include <string>
#include <cassert> // Для assert
#include <numeric> // Для std::accumulate

using namespace std;

// Генерация гаммы
string generateKey(const string& key, size_t length) 
{
    string generatedKey;
    for (size_t i = 0; i < length; ++i) 
    {
        generatedKey += key[i % key.size()];
    }
    return generatedKey;
}

// XOR шифрование
string xorCipher(const string& data, const string& key) 
{
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) 
    {
        result[i] = data[i] ^ key[i];
    }
    return result;
}

// Вычисление контрольной суммы
unsigned int calculateChecksum(const string& text) 
{
    return accumulate(text.begin(), text.end(), 0u);
}

// Тест для generateKey
void testGenerateKey() 
{
    string key = "abc";
    assert(generateKey(key, 6) == "abcabc");
    assert(generateKey(key, 4) == "abca");
    assert(generateKey(key, 2) == "ab");
    cout << "Тесты для generateKey прошли успешно." << endl;
}

// Тест для xorCipher
void testXorCipher() 
{
    string text = "hello";
    string key = "abcde";
    string encrypted = xorCipher(text, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == text); // После дешифрования должно быть то же самое
    assert(encrypted != text); // Зашифрованный текст не должен быть равен исходному
    cout << "Тесты для xorCipher прошли успешно." << endl;
}

// Тест для calculateChecksum
void testCalculateChecksum() 
{
    string text = "hello";
    unsigned int checksum = calculateChecksum(text);
    assert(checksum == ('h' + 'e' + 'l' + 'l' + 'o')); // Проверяем сумму символов
    assert(calculateChecksum("") == 0); // Для пустого текста сумма должна быть 0
    cout << "Тесты для calculateChecksum прошли успешно." << endl;
}

// Общий тест для шифрования/дешифрования с контрольной суммой
void testEncryptionDecryptionWithChecksum() 
{
    string text = "test message";
    string gamma = "key";
    string key = generateKey(gamma, text.size());
    string encrypted = xorCipher(text, key);
    string decrypted = xorCipher(encrypted, key);
    unsigned int originalChecksum = calculateChecksum(text);
    unsigned int decryptedChecksum = calculateChecksum(decrypted);

    assert(decrypted == text); // Дешифрованный текст должен совпадать с исходным
    assert(originalChecksum == decryptedChecksum); // Контрольные суммы должны совпадать
    cout << "Тесты для полного процесса шифрования/дешифрования с контрольной суммой прошли успешно." << endl;
}

int main() 
{
    // Запуск тестов
    testGenerateKey();
    testXorCipher();
    testCalculateChecksum();
    testEncryptionDecryptionWithChecksum();

    cout << "Все тесты прошли успешно!" << endl;

    return 0;
}

