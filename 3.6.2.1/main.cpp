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
    setlocale(LC_ALL, "Russian");

    string inputFileName;
    string outputFileName;

    wcout << L"Введите имя входного файла: " << endl;
    cin >> inputFileName;

    wcout << L"Введите имя выходного файла: " << endl;
    cin >> outputFileName;

    // Чтение из файла
    string line;
    string text;

    ifstream inputFile(inputFileName);
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            text += line + '\n';
        }
        inputFile.close();
    } else {
        wcout << L"Ошибка открытия файла" << endl;
        return 1;
    }
    cout << text << endl;


    int key1 = 1;
    int key2;


    while (true)
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

    //Добавление контрольной суммы
    char kontSum = kontrolnayaSumma(text, key2);
    text += kontSum;

// шифрование текста
        string gamma = generateGamma(key1);
        string encode_Text = encode(text, gamma);
/*
        wcout << L"Зашифрованные данные: " << endl;
        cout << encode_Text << endl;

        string not_encryptedData = encode(encode_Text, gamma);
        wcout << L"Расшифрованные данные: " << endl;
        cout << not_encryptedData << endl;
*/

        ofstream outputFile(outputFileName);
        if (outputFile.is_open()) {
            outputFile << encode_Text;
            outputFile.close();
        } else {
            wcout << L"Ошибка открытия файла для записи" << endl;
            return 1;
        }

        wcout << L"Файл зашифрован и записан, гамма: " << key1 << endl;
        key1 = (key1 % 3) + 1;

        string decryptedtext = encode(encode_Text, gamma);

         // Извлечение контрольной суммы
        char kontAfterSum = decryptedtext.back();
        decryptedtext.pop_back();

        // Проверка контрольной суммы
        kontSum = kontrolnayaSumma(decryptedtext, key2);
        if (kontSum == kontAfterSum) {
            wcout << L"Контрольная сумма совпадает. Дешифрование успешно!" << endl;
        } else {
            wcout << L"Контрольная сумма не совпадает." << endl;
        }

        // Ожидание следующего цикла
        this_thread::sleep_for(chrono::seconds(20)); // остановка до следующей гаммы


    }


}
