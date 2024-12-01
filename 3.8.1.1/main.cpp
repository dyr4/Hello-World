#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

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

int main() {
    setlocale(LC_ALL, "Russian");

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";

    // Чтение исходного текста из файла
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

    // Вычисление контрольной суммы исходного текста
    char originalChecksum = calculateChecksum(text);
    cout << "Контрольная сумма исходного текста: " << (int)originalChecksum << endl;

    // Определение длины открытого текста
    size_t textLength = text.size();
    cout << "Длина открытого текста: " << textLength << endl;

    int cycle = 1; // Начальное значение цикла гаммы
    while (true) {
        // Выбор гаммы в зависимости от текущего цикла
        string gamma = selectGamma(cycle);
        cout << "Используемая гамма: " << gamma << endl;

        // Генерация ключа нужной длины
        string generatedKey = generateKey(gamma, text.size());

        // Шифрование текста
        string ciphertext = xorCipher(text, generatedKey);
        cout << "\nЗашифрованный текст:\n\n" << ciphertext << endl;

        // Добавление длины открытого текста и контрольной суммы к зашифрованному тексту
        ciphertext.insert(0, reinterpret_cast<const char*>(&textLength), sizeof(textLength));
        ciphertext += originalChecksum;

        // Запись зашифрованного текста в файл
        ofstream outputFile(file_out, ios::binary);
        if (!outputFile.is_open()) {
            cout << "Ошибка при открытии файла " << file_out << endl;
            return 1;
        }
        outputFile.write(ciphertext.data(), ciphertext.size());
        outputFile.close();

        cout << "Файл зашифрован и записан. ЦИКЛ ГАММЫ: " << cycle << endl;

        // Имитация чтения из файла для расшифровки
        ifstream inputFile(file_out, ios::binary);
        if (!inputFile.is_open()) {
            cout << "Ошибка при открытии файла " << file_out << endl;
            return 1;
        }
        string encryptedText((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
        inputFile.close();

        // Извлечение длины открытого текста из зашифрованного текста
        size_t extractedTextLength;
        memcpy(&extractedTextLength, encryptedText.data(), sizeof(extractedTextLength));
        encryptedText.erase(0, sizeof(extractedTextLength));

        // Извлечение контрольной суммы из зашифрованного текста
        char storedChecksum = encryptedText.back();
        encryptedText.pop_back();

        // Проверка контрольной суммы
        if (originalChecksum != storedChecksum) {
            cout << "Ошибка: контрольная сумма не совпадает! Файл поврежден." << endl;
            return 1;
        }

        // Расшифровка текста
        string decryptedText = xorCipher(encryptedText, generatedKey);
        cout << "\nРасшифрованный текст:\n\n" << decryptedText << endl;

        // Проверка корректности расшифровки
        if (decryptedText == text) {
            cout << "Расшифровка успешна! Ожидание следующей гаммы...\n" << endl;

        } else {
            cout << "Ошибка: расшифрованный текст не совпадает с исходным!" << endl;
        }

        // Переход к следующему циклу гаммы
        cycle = (cycle % 3) + 1;

        // Ожидание 20 секунд перед следующим циклом
        this_thread::sleep_for(chrono::seconds(20));
    }

    return 0;
}
