#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>

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

int main() {
    setlocale(LC_ALL, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";

    // Чтение всего содержимого из файла
    string text;
    ifstream fileIn(file_in);
    if (fileIn.is_open()) {
        stringstream buffer;
        buffer << fileIn.rdbuf();
        text = buffer.str();
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    // Вычисление контрольной суммы на основе исходного текста
    char originalChecksum = calculateChecksum(text);
    cout << "Контрольная сумма исходного текста: " << (int)originalChecksum << endl;

    // Определение длины открытого текста
    size_t textLength = text.size();
    cout << "Длина открытого текста: " << textLength << endl;

    string chooseDay;
    cout << "Взять дату из системы? (Yes or No): ";
    cin >> chooseDay;
    int gammaType;

    if (chooseDay == "Yes" || chooseDay == "yes") {
        gammaType = getDay();
    } else if (chooseDay == "No" || chooseDay == "no") {
        cout << "Введите число: ";
        cin >> gammaType;
    } else {
        cout << "Некорректный ввод" << endl;
        return 0;
    }

    // Выбор гаммы
    string gamma;
    if (gammaType % 2 == 0) {
        gamma = "ABCDEFGHIJKLMNOP";
    } else {
        gamma = "GHEFABCDOPMNIJKL";
    }

    // Генерация ключа нужной длины
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);
    cout << "\nЗашифрованный текст:\n\n" << ciphertext << endl;

    // Добавление контрольной суммы к зашифрованному тексту
    ciphertext += originalChecksum;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }
    outputFile << ciphertext;
    outputFile.close();

    // Чтение зашифрованного текста из файла для расшифровки
    ifstream inputFile(file_out);
    if (!inputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }
    string encryptedText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();

    // Извлечение контрольной суммы из зашифрованного текста
    char storedChecksum = encryptedText.back();
    encryptedText.pop_back();

    // Проверка контрольной суммы
    if (originalChecksum != storedChecksum) {
        cout << "Ошибка: контрольная сумма не совпадает! Файл повреждён." << endl;
        return 1;
    }

    // Дешифрование текста
    string decryptedText = xorCipher(encryptedText, generatedKey);
    cout << "\nРасшифрованный текст:\n\n" << decryptedText << endl;

    return 0;
}
