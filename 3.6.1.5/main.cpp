#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;



char calculateChecksum(const string& data) {
    char checksum = 0;
    for (char c : data) {
        checksum ^= c;
    }
    return checksum;
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


string encode(const string& data, const string& gamma)
{
    string encode_Data;
    size_t sizeGamma = gamma.size();

    for (size_t i = 0; i < data.size(); i++)
    {
        char current_Gamma = gamma[i % sizeGamma]; // повтор гаммы
        encode_Data.push_back(data[i] ^ current_Gamma); // Шифрование с помощью XOR
    }

    return encode_Data;
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

string readFile()
{

    string inputFileName = "file_in.txt";
    string text;
    ifstream inputFile(inputFileName, ios::binary);
    if (inputFile.is_open()) {
        stringstream buffer;
        buffer << inputFile.rdbuf();
        text = buffer.str();
        inputFile.close();
    }
    else
    {
        cout << "Ошибка: Не удалось открыть файл " << inputFileName << endl;
    }
//    cout << text << endl;

    return text;
}



void writeFile(string encode_Text)
{

    string outputFileName = "file_out.txt";

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



int main()
{
    setlocale(LC_ALL, "Russian");

    string text1 = readFile();
    char originalChecksum = calculateChecksum(text1);




    cout << "Контрольная сумма исходного текста: " << (int)originalChecksum << endl;
    // Добавление контрольной суммы к зашифрованному тексту
    text1 += originalChecksum;

    //Выбор гаммы для шифрования
    string gammaType = chooseGammaType(text1);
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Латинская гамма
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Кириллическая гамма
    }
    string encode_Text1 = encode(text1, gamma);

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


    string encode_Text2 = encode(encode_Text1, marcant);
    writeFile(encode_Text2);
    cout << "Зашифрованные данные: " << endl;
    cout << encode_Text2 << endl;



    string not_encrcode_marcant = encode(encode_Text2, marcant);
    string not_encode = encode(not_encrcode_marcant, gamma);
    cout << "Расшифрованные данные: " << endl;
    cout << not_encode << endl;



    // Извлечение контрольной суммы из зашифрованного текста
    char storedChecksum = not_encode.back();
    not_encode.pop_back();
    cout << storedChecksum << endl;
    cout << not_encode << endl;


    // Проверка контрольной суммы
    if (originalChecksum != storedChecksum)
    {
        cout << "Ошибка: контрольная сумма не совпадает! Файл поврежден." << endl;
        return 1;
    }






    return 0;
}
