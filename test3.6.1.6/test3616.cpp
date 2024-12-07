#include <iostream>
#include <string>
#include <cassert>

// Подключаем функции из основного файла
#include "main.cpp"

// Функция для теста генерации ключа
void testGenerateKey() {
    string text = "Hello world! We the best team";
    string key = "forest";
    string generatedKey = generateKey(key, text.size());
    assert(generatedKey == "forestforestforestforestfores");
    std::cout << "Test Passed: Key Generation\n";
}

// Функция для теста XOR шифрования/дешифрования
void testXorCipher() {
    string data = "Hello, World!";
    string key = "key";
    string encrypted = xorCipher(data, key);
    string decrypted = xorCipher(encrypted, key);
    assert(decrypted == data);
    std::cout << "Test Passed: XOR Cipher\n";
}

// Функция для теста выбора типа гаммы
void testChooseGammaType() {
    string text = "Проверка текста, мы the best команда";
    assert(chooseGammaType(text) == "cirillic");

    text = "Проверка текста, we the best team";
    assert(chooseGammaType(text) == "latin");

    std::cout << "Test Passed: Gamma Type Selection\n";
}

// Функция для теста получения дня недели
void testDay() {
    int day = Day();
    assert(day >= 0 && day <= 6); // Проверка, что день недели в диапазоне 0-6
    std::cout << "Test Passed: Day of the Week\n";
}

// Функция для теста генерации гаммы
void testGenerateGamma() {
    assert(generateGamma(1) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(2) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(3) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(4) == "GHEF OPMN ABCD IJKL");
    assert(generateGamma(5) == "ABCD EFGH IJKL MNOP");
    assert(generateGamma(6) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(7) == "GHEF CDAB OPMN KLIJ");
    assert(generateGamma(8) == "");  // Некорректный день недели
    std::cout << "Test Passed: Gamma Generation\n";
}

// Основная функция для запуска тестов
int main() {
    testGenerateKey();
    testXorCipher();
    testChooseGammaType();
    testDay();
    testGenerateGamma();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}

