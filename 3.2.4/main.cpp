#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;


string generateGamma(int key1) {
    switch (key1) {
        case 1:
            return "ABCD EFGH IJKL MNOP";
        case 2:
            return "GHAB OPIJ MNCD KLEF";
        case 3:
            return "GHEF CDAB OPMN KLIJ";
        default:
            return "";
    }
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
    string gammaType = chooseGammaType(text1);
// Выбор гаммы
    string gamma;
    if (gammaType == "latin") {
        gamma = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; // Латинская гамма
    } else {
        gamma = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"; // Кириллическая гамма
    }

    string encode_Text1 = encode(text1, gamma);

/*
    cout << gammaType << endl;
    cout << gamma << endl;
    cout << encode_Text1 << endl;
*/

    int key1 = 1;
    while (true)
    {

// шифрование текста
        string gamma_20 = generateGamma(key1);
        string encode_Text2 = encode(encode_Text1, gamma_20);
        cout << "Зашифрованные данные: " << endl;
        cout << encode_Text2 << endl;

        string not_encryptedData = encode(encode_Text2, gamma_20);
        cout << "Расшифрованные данные: " << endl;
        cout << encode(not_encryptedData, gamma)  << endl;


        writeFile(encode_Text2);

        cout << "Файл зашифрован и записан, гамма: " << key1 << endl;
        key1 = (key1 % 3) + 1;

        // Ожидание следующего цикла
        this_thread::sleep_for(chrono::seconds(20)); // остановка до следующей гаммы



    }
}

