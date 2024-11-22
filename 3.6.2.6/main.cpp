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

    auto t1 = chrono::system_clock::now();

    // time_point в time_t
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    int l = local_tm->tm_wday;
    return local_tm->tm_wday;
}

//Функция для выбора гаммы в зависимости от дня недели
string generateGamma(int dayW)
{
    switch(dayW)
    {
        case 1:
        case 3:
        case 5:
            return "ABCD EFGH IJKL MNOP";
        case 2:
        case 4:
            return "GHEF OPMN ABCD IJKL";
        case 6:
        case 7:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
}

// Функция для чтения файла
string readFile()
{
    string inputFileName;
    cout << "Введите имя входного файла: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        cout << "Ошибка открытия файла" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
}

void writeFile(string encode_Text)
{

    string outputFileName;
    cout << "Введите имя файла, в который запишутся зашифрованные данные" << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
    } else {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }

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

    //Чтение открытого текста
    string text = readFile();

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
    string marcant = generateGamma(Day());

    //Создание ключа марканта
    generatedKey = generateKey(marcant, text.size()); // Используем введенный ключ
    cout << "Генерация ключа с маркантом: " << generatedKey << endl;

    // Шифрование с маркантом
    string ciphertextwithmarcan = xorCipher(ciphertext, generatedKey);
    cout << "Зашифрованный текст: " << ciphertextwithmarcan << endl;

    //Запись зашифрованного текста в файл
    writeFile(text);

    // Дешифрование текста с использованием того же ключа
    string decryptedtextwithmarcan = xorCipher(ciphertextwithmarcan, generatedKey);
    generatedKey = generateKey(gamma, text.size());
    string decryptedtext=xorCipher(decryptedtextwithmarcan, generatedKey);
    cout << "Расшифрованный текст: " << decryptedtext << endl;

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

    }
    return 0;
}
