#include <iostream>
#include <fstream>
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
        result[i] = data[i] ^ key[i]; // Используем XOR для шифрования и дешифрования
    }
    return result;
}

// Функция для определения гаммы
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (char c : text) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) { // Подсчёт латинских символов
            latinCount++;
        } else if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) { // Подсчёт кириллицы
            cirillicCount++;
        }
    }
    if(latinCount > cirillicCount)
    {
        return "latin";
    }
    else
    {
        return "cirillic";
    }
}

// Функция для вычисления числа месяца
int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "Текущая дата: " << buf << endl;

    return stoi(buf);
}

// Функция для добавления байта длины в конец текста
string addLengthByte(const string& data) {
    char lengthByte = static_cast<char>(data.size()); // Определение длины текста
    return data + lengthByte; // Добавление байта длины в конец
}

// Функция для извлечения длины из зашифрованного текста
size_t extractLengthFromCiphertext(const string& data) {
    return static_cast<size_t>(static_cast<unsigned char>(data.back())); // Получаем длину из последнего байта
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
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Латинская гамма
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Кириллическая гамма
    }

    // Генерация ключа
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;

    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);

    // Добавляем байт длины в конец текста
    ciphertext = addLengthByte(ciphertext);

    // Выбор гаммы марканта
    int Date;
    string chooseDay;
    cout << "Взять дату из системы?(Yes or No)" << endl;
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
        marcant = "ABCDEFGHIJKLMNOP"; // Гамма при чётном числе месяца
    } else {
        marcant = "GHEFABCDOPMNIJKL"; // Гамма при нечётном числе месяца
    }

    // Создание ключа марканта
    generatedKey = generateKey(marcant, text.size()); // Используем введенный ключ
    cout << "Генерация ключа с маркантом: " << generatedKey << endl;

    // Шифрование с маркантом
    string ciphertextwithmarcan = xorCipher(ciphertext, generatedKey);
    cout << "Зашифрованный текст: " << ciphertextwithmarcan << endl;

    // Запись зашифрованного текста в файл
    ofstream outputFile(file_out);
    if (!outputFile.is_open()) {
        cout << "Ошибка при открытии файла " << file_out << endl;
        return 1;
    }

    outputFile << ciphertextwithmarcan;
    outputFile.close();

    // Дешифрование текста с использованием того же ключа
    string decryptedtextwithmarcan = xorCipher(ciphertextwithmarcan, generatedKey);

    // Извлекаем длину из зашифрованного текста
    size_t originalLength = extractLengthFromCiphertext(decryptedtextwithmarcan);

    // Убираем байт длины и дешифруем остаток
    string decryptedtext = xorCipher(decryptedtextwithmarcan.substr(0, originalLength), generatedKey);
    cout << "Расшифрованный текст: " << decryptedtext << endl;

    return 0;
}
