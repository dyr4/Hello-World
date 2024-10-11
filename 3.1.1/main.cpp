#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; //Генерируем ключ нужный длины
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // Используем XoR для шифрования и дешифрования
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
    }
    else
    {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
    }

    // Выбор гаммы
    string gamma = "2";

    // Генерация ключа нужной длины
    string generatedKey = generateKey(gamma, text.size()); // Используем введенный ключ
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);
    cout << "Зашифрованный текст: " << ciphertext << endl;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // Дешифрование текста
    string decryptedtext = xorCipher(ciphertext, generatedKey);
    cout << "Расшифрованный текст: " << decryptedtext << endl;

    return 0;
}
