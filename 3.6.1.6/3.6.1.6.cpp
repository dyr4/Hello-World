#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cassert>
#include <numeric>  // Для вычисления контрольной суммы

using namespace std;

// Функция для генерации ключа
string generateKey(const string& key, size_t length) {
    string generatedKey;
    for (size_t i = 0; i < length; ++i) {
        generatedKey += key[i % key.size()]; // Использование ключа по кругу
    }
    return generatedKey;
}

// Функция для шифрования и дешифрования с помощью XOR
string xorCipher(const string& data, const string& key) {
    string result = data;
    for (size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i]; // Применение XOR для шифрования и дешифрования
    }
    return result;
}

// Функция для генерации марканта (например, по длине текста)
string generateMarkant(const string& data) {
    return "Markant_" + to_string(data.size());
}

// Функция для вычисления контрольной суммы
unsigned int calculateChecksum(const string& data) {
    return accumulate(data.begin(), data.end(), 0U);
}

// Функция для выбора типа гаммы
string chooseGammaType(const string& text) {
    int latinCount = 0;
    int cirillicCount = 0;

    for (wchar_t c : text) {
        if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || (c >= L'0' && c <= L'9')) { // Проверка латинских символов и цифр
            latinCount++;
        } else if ((c >= L'À' && c <= L'ß') || (c >= L'à' && c <= L'ÿ')) { // Проверка кириллических символов
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

// Функция для получения текущего дня недели
int Day()
{
    auto t1 = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(t1);
    tm* local_tm = localtime(&currentTime);
    return local_tm->tm_wday;
}

// Функция для генерации гаммы в зависимости от дня недели
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

// Функция для чтения данных из файла
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
        cout << "Файл успешно прочитан" << endl;
        inputFile.close();
    } else {
        cout << "Не удалось открыть файл" << endl;
        return "";
    }

    return text;
}

// Функция для записи данных в файл
void writeFile()
{
    string outputFileName;
    cout << "Введите имя файла для записи" << endl;
    cin >> outputFileName;
    string encode_Text = "Зашифрованный текст";
    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
        cout << "В файл успешно записан результат" << endl;
    } else {
        cout << "Не удалось открыть файл для записи" << endl;
        return;
    }
}

int main()
{
    setlocale(0, "Russian");

    // Пример генерации марканта
    string text = "Hello world!";
    string markant = generateMarkant(text);
    cout << "Маркант: " << markant << endl;

    // Пример вычисления контрольной суммы
    unsigned int checksum = calculateChecksum(text);
    cout << "Контрольная сумма: " << checksum << endl;

    readFile();
    writeFile();

    return 0;
}

