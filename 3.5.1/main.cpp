#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// Функция для генерации гаммы в зависимости от цикла
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

// шифрование
string encode(const string& data, const string& gamma) {
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
    wcout << L"Введите имя входного файла: " << endl;
    cin >> inputFileName;
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line)) {
            text += line;
        }
        inputFile.close();
    } else {
        wcout << L"Ошибка открытия файла" << endl;
        return "";
    }
//    cout << text << endl;

    return text;
}



void writeFile(string encode_Text)
{

    string outputFileName;
    wcout << L"Введите имя файла, в который запишутся зашифрованные данные" << endl;
    cin >> outputFileName;

    ofstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        outputFile << encode_Text;
        outputFile.close();
    } else {
        wcout << L"Ошибка открытия файла для записи" << endl;
        return;
    }

}

int main() {
    setlocale(LC_ALL, "Russian");

    string text = readFile();

// Добавление байта с длиной открытого текста
    char lengthByte = static_cast<char>(text.size());

    text += lengthByte; //  Добавляем байт длины
//  cout << lengthByte << endl;

    int key1 = 1;


    while (true)
    {

// шифрование текста
        string gamma = generateGamma(key1);
        string encode_Text = encode(text, gamma);



        wcout << L"Зашифрованные данные: " << endl;
        cout << encode_Text << endl;

        string decryptedtext = encode(encode_Text, gamma);
        int originalLength = static_cast<unsigned char>(decryptedtext.back()); // Получаем длину из последнего байта
        wcout << L"Расшифрованный текст: " << endl;
        cout << decryptedtext.substr(0, originalLength) << endl;


        writeFile(encode_Text);

        key1 = (key1 % 3) + 1;

        // Ожидание следующего цикла
        this_thread::sleep_for(chrono::seconds(20)); // остановка до следующей гаммы

    }



}
