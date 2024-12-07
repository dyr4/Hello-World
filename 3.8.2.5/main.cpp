#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

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
        result[i] = data[i] ^ key[i]; // Используем XOR для шифрования и дешифрования
    }
    return result;
}

// Функция для определения гаммы
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            latinCount++;
        } else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) {
            cirillicCount++;
        }
    }
    if (latinCount > cirillicCount) {
        return "latin";
    } else {
        return "cirillic";
    }
}

// Функция для вычисления числа месяца
int Day() {
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "Текущая дата: " << buf << endl;

    return stoi(buf);
}

// Функция для вычисления контрольной суммы, зависящей от времени
string generateChecksum() {
    time_t now = time(nullptr);
    stringstream ss;
    ss << now; // Используем время в секундах с начала эпохи как контрольную сумму
    return ss.str();
}

int main() {
    setlocale(0, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string text;

    // Открытие файла с открытым текстом
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    // Выбор гаммы для шифрования
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    }

    // Генерация ключа
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);

    // Выбор гаммы марканта
    int Date;
    string chooseDay;
    cout << "Взять дату из системы? (Yes or No)" << endl;
    cin >> chooseDay;

    if (chooseDay == "Yes" || chooseDay == "yes") {
        Date = Day();
    } else if (chooseDay == "No" || chooseDay == "no") {
        cout << "Введите число: ";
        cin >> Date;
    } else {
        cout << "Некорректный ввод" << endl;
        return 0;
    }

    string marcant;
    if (Date % 2 == 0) {
        marcant = "ABCDEFGHIJKLMNOP";
    } else {
        marcant = "GHEFABCDOPMNIJKL";
    }

    // Создание ключа марканта
    generatedKey = generateKey(marcant, text.size());
    cout << "Генерация ключа с маркантом: " << generatedKey << endl;

    // Добавление длины текста и контрольной суммы в шифрованный текст
    string lengthField = to_string(text.size());
    string checksum = generateChecksum();
    ciphertext = lengthField + ":" + checksum + ":" + xorCipher(ciphertext, generatedKey);

    cout << "Зашифрованный текст с длиной и контрольной суммой: " << ciphertext << endl;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile << ciphertext;
    outputFile.close();

    // Расшифрование текста с использованием ключей
    size_t delimiter1 = ciphertext.find(":");
    size_t delimiter2 = ciphertext.find(":", delimiter1 + 1);

    string encryptedData = ciphertext.substr(delimiter2 + 1);
    string decryptedtextwithmarcan = xorCipher(encryptedData, generatedKey);
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext = xorCipher(decryptedtextwithmarcan, generatedKey);

    cout << "Расшифрованный текст: " << decryptedtext << endl;

    return 0;
}
