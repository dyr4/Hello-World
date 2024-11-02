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

// Подсчёт контрольной суммы
char kontrolnayaSumma(const string& text)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    return static_cast<char>(checksum);
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

    string gammaType = chooseGammaType(text);

    // Выбор гаммы
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Латинская гамма
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Кириллическая гамма
    }

    // Генерация ключа нужной длины
    string generatedKey = generateKey(gamma, text.size()); // Используем введенный ключ
    cout << "Генерация ключа: " << generatedKey << endl;

    // Подсчёт контрольной суммы
    char kontSum = kontrolnayaSumma(text);
    text += kontSum;

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

     // Извлечение контрольной суммы
    char kontAfterSum = decryptedtext.back();
    decryptedtext.pop_back();

    // Проверка контрольной суммы
    kontSum = kontrolnayaSumma(decryptedtext);
    if (kontSum == kontAfterSum) {
        cout << "Контрольная сумма совпадает. Дешифрование успешно!" << endl;
    } else {
        cout << "Контрольная сумма не совпадает." << endl;
    }

    return 0;
}
