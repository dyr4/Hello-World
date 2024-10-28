#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // Генерируем ключ нужной длины
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // Используем XOR для шифрования и дешифрования
    }
    return result;
}

int main() {
    setlocale(0, "Russian");

    string file_in, file_out;
    file_in = "file_in.txt";
    file_out = "file_out.txt";

    // Чтение текста из файла
    string text;
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1; // Завершаем программу при ошибке
    }

    // Выбор гаммы
    string gamma = "2";

    // Генерация ключа нужной длины
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);

    // Добавление байта с длиной открытого текста
    char lengthByte = static_cast<char>(text.size());
    ciphertext += lengthByte; //  Добавляем байт длины

    cout << "Зашифрованный текст: " << ciphertext << endl;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out, ios::binary); // Открываем файл в бинарном режиме
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile.write(ciphertext.c_str(), ciphertext.size());
    outputFile.close();

    // Дешифрование текста
    int originalLength = static_cast<unsigned char>(ciphertext.back()); // Получаем длину из последнего байта
    string decryptedtext = xorCipher(ciphertext.substr(0, ciphertext.size() - 1), generatedKey); // Убираем последний байт
    cout << "Расшифрованный текст: " << decryptedtext.substr(0, originalLength) << endl; // Выводим только оригинальную длину

    return 0;
}

