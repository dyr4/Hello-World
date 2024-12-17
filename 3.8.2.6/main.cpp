#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
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

// Функция для определения типа гаммы
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cyrillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            latinCount++;
        } else if ((c >= '\u0410' && c <= '\u042F') || (c >= '\u0430' && c <= '\u044F')) {
            cyrillicCount++;
        }
    }
    return latinCount > cyrillicCount ? "latin" : "cyrillic";
}

// Функция для вычисления дня недели
int Day() {
    auto t1 = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    return local_tm->tm_wday;
}

// Функция для выбора гаммы в зависимости от дня недели
string generateGamma(int dayW) {
    switch (dayW) {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 0:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Функция для вычисления контрольной суммы, зависящей от времени
string generateChecksum() {
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%Y%m%d%H%M%S");
    string timestamp = ss.str();

    string checksum;
    for (char c : timestamp) {
        checksum += (c % 256);
    }
    return checksum;
}

// Функция для чтения файла
string readFile() {
    string inputFileName;
    cout << "Введите имя входного файла: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        cout << "Ошибка открытия файла" << endl;
        return "";
    }
    return text;
}

// Функция для записи зашифрованных данных в файл
void writeFile(const string& encodedText) {
    string outputFileName;
    cout << "Введите имя файла для записи зашифрованных данных: " << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        outputFile << encodedText;
        outputFile.close();
    } else {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }
}

int main() {
    setlocale(0, "Russian");

    // Чтение открытого текста
    string text = readFile();

    // Выбор гаммы для шифрования
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    } else {
        gamma = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя";
    }

    // Генерация ключа
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);

    // Добавление контрольной суммы
    string checksum = generateChecksum();
    ciphertext = checksum + to_string(text.size()) + ciphertext;

    // Генерация гаммы с учетом дня недели
    string marcant = generateGamma(Day());

    // Создание ключа с маркантом
    generatedKey = generateKey(marcant, ciphertext.size());
    cout << "Генерация ключа с маркантом: " << generatedKey << endl;

    // Шифрование с маркантом
    string ciphertextWithMarcant = xorCipher(ciphertext, generatedKey);
    cout << "Зашифрованный текст: " << ciphertextWithMarcant << endl;

    // Запись зашифрованного текста в файл
    writeFile(ciphertextWithMarcant);

    // Дешифрование текста с использованием того же ключа
    string decryptedTextWithMarcant = xorCipher(ciphertextWithMarcant, generatedKey);

    // Извлечение контрольной суммы и длины текста
    string extractedChecksum = decryptedTextWithMarcant.substr(0, checksum.size());
    size_t length = stoi(decryptedTextWithMarcant.substr(checksum.size(), to_string(text.size()).size()));
    string extractedCiphertext = decryptedTextWithMarcant.substr(checksum.size() + to_string(text.size()).size());

    // Проверка контрольной суммы
    if (extractedChecksum != checksum) {
        cout << "Ошибка: контрольная сумма не совпадает." << endl;
        return 1;
    }

    // Дешифрование оставшегося текста
    generatedKey = generateKey(gamma, length);
    string decryptedText = xorCipher(extractedCiphertext, generatedKey);
    cout << "Расшифрованный текст: " << decryptedText << endl;

    return 0;
}
