#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>

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

// Функция для вычесления числа месяца
int Day()
{
    time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, sizeof(buf), "%d", localtime(&tm));

    cout << "Текущая дата: " << buf << endl;

    return stoi(buf);
}

// Подсчёт контрольной суммы
char kontrolnayaSumma(const string& text, int key2)
{
    int checksum = 0;
    for (int i = 0; i < text.length(); i++) {
        checksum += (int)text[i];
    }
    checksum += key2;

    return static_cast<char>(checksum);
}


int main() {

    string file_in = "file_in.txt";
    string file_out = "file_out.txt";
    string text;

    //Открытие файла с открытом текстом
    ifstream fileIn(file_in);

    if (fileIn.is_open()) {
        getline(fileIn, text);
        fileIn.close();
    } else {
        cout << "Ошибка: Не удалось открыть файл " << file_in << endl;
        return 1;
    }

    int key1 = 1;
    int key2;

    while(true)
    {

    switch(key1){
        case 1:
            key2 = 20;
        case 2:
            key2 = 40;
        case 3:
            key2 = 60;
        default:
            key2 = 0;
    }

    key1 = (key1 % 3) + 1;

    //Выбор гаммы для шифрования
    string gammaType = chooseGammaType(text);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Латинская гамма
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Кириллическая гамма
    }

    //Добавление контрольной суммы
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

    //Генерация ключа
    string generatedKey = generateKey(gamma, text.size());
    cout << "Генерация ключа: " << generatedKey << endl;



    // Шифрование
    string ciphertext = xorCipher(text, generatedKey);

    //Выбор гаммы марканта
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

    //Создание ключа марканта
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
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext=xorCipher(decryptedtextwithmarcan, generatedKey);

    cout<<"Рассшифрованный файл: " << decryptedtext<<endl;

    // Извлечение контрольной суммы
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // Проверка контрольной суммы
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            cout << "Контрольная сумма совпадает. Дешифрование успешно!" << endl;
        } else {
            cout << "Контрольная сумма не совпадает." << endl;
        }

        // Ожидание следующего цикла
        this_thread::sleep_for(chrono::seconds(20)); // остановка до следующей гаммы

    cout << "Расшифрованный текст: " << decryptedtext << endl;


    }

    return 0;
}
